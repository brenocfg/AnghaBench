#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pblk_sec_meta {int /*<<< orphan*/  lba; } ;
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct pblk_pr_ctx {int bi_vcnt; unsigned int bio_init_idx; int orig_nr_secs; int /*<<< orphan*/  dma_ppa_list; int /*<<< orphan*/ * ppa_ptr; int /*<<< orphan*/  bitmap; struct pblk_pr_ctx* orig_bio; TYPE_1__ bi_iter; } ;
struct pblk_g_ctx {struct pblk_pr_ctx* private; } ;
struct pblk {int dummy; } ;
struct nvm_rq {int nr_ppas; int /*<<< orphan*/ * ppa_list; int /*<<< orphan*/  ppa_addr; int /*<<< orphan*/  dma_ppa_list; int /*<<< orphan*/  flags; struct pblk_pr_ctx* bio; struct pblk_sec_meta* meta_list; } ;
struct bio {int bi_vcnt; unsigned int bio_init_idx; int orig_nr_secs; int /*<<< orphan*/  dma_ppa_list; int /*<<< orphan*/ * ppa_ptr; int /*<<< orphan*/  bitmap; struct bio* orig_bio; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVM_MAX_VLBA ; 
 int /*<<< orphan*/  PBLK_READ_RANDOM ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 struct pblk_pr_ctx* bio_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_put (struct pblk_pr_ctx*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct pblk_pr_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 struct pblk_pr_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct pblk_g_ctx* nvm_rq_to_pdu (struct nvm_rq*) ; 
 scalar_t__ pblk_bio_add_pages (struct pblk*,struct pblk_pr_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pblk_bio_free_pages (struct pblk*,struct pblk_pr_ctx*,int /*<<< orphan*/ ,int) ; 
 int pblk_dma_ppa_size ; 
 int /*<<< orphan*/  pblk_set_read_mode (struct pblk*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pblk_setup_partial_read(struct pblk *pblk, struct nvm_rq *rqd,
			    unsigned int bio_init_idx,
			    unsigned long *read_bitmap,
			    int nr_holes)
{
	struct pblk_sec_meta *meta_list = rqd->meta_list;
	struct pblk_g_ctx *r_ctx = nvm_rq_to_pdu(rqd);
	struct pblk_pr_ctx *pr_ctx;
	struct bio *new_bio, *bio = r_ctx->private;
	__le64 *lba_list_mem;
	int nr_secs = rqd->nr_ppas;
	int i;

	/* Re-use allocated memory for intermediate lbas */
	lba_list_mem = (((void *)rqd->ppa_list) + pblk_dma_ppa_size);

	new_bio = bio_alloc(GFP_KERNEL, nr_holes);

	if (pblk_bio_add_pages(pblk, new_bio, GFP_KERNEL, nr_holes))
		goto fail_bio_put;

	if (nr_holes != new_bio->bi_vcnt) {
		WARN_ONCE(1, "pblk: malformed bio\n");
		goto fail_free_pages;
	}

	pr_ctx = kmalloc(sizeof(struct pblk_pr_ctx), GFP_KERNEL);
	if (!pr_ctx)
		goto fail_free_pages;

	for (i = 0; i < nr_secs; i++)
		lba_list_mem[i] = meta_list[i].lba;

	new_bio->bi_iter.bi_sector = 0; /* internal bio */
	bio_set_op_attrs(new_bio, REQ_OP_READ, 0);

	rqd->bio = new_bio;
	rqd->nr_ppas = nr_holes;
	rqd->flags = pblk_set_read_mode(pblk, PBLK_READ_RANDOM);

	pr_ctx->ppa_ptr = NULL;
	pr_ctx->orig_bio = bio;
	bitmap_copy(pr_ctx->bitmap, read_bitmap, NVM_MAX_VLBA);
	pr_ctx->bio_init_idx = bio_init_idx;
	pr_ctx->orig_nr_secs = nr_secs;
	r_ctx->private = pr_ctx;

	if (unlikely(nr_holes == 1)) {
		pr_ctx->ppa_ptr = rqd->ppa_list;
		pr_ctx->dma_ppa_list = rqd->dma_ppa_list;
		rqd->ppa_addr = rqd->ppa_list[0];
	}
	return 0;

fail_free_pages:
	pblk_bio_free_pages(pblk, new_bio, 0, new_bio->bi_vcnt);
fail_bio_put:
	bio_put(new_bio);

	return -ENOMEM;
}