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
struct request_queue {int dummy; } ;
struct pblk_g_ctx {struct bio* private; int /*<<< orphan*/  lba; int /*<<< orphan*/  start_time; } ;
struct pblk {int /*<<< orphan*/  inflight_io; TYPE_1__* disk; struct nvm_tgt_dev* dev; } ;
struct nvm_tgt_dev {struct request_queue* q; } ;
struct nvm_rq {unsigned int nr_ppas; int /*<<< orphan*/  error; int /*<<< orphan*/ * ppa_list; int /*<<< orphan*/  ppa_addr; struct bio* bio; int /*<<< orphan*/  (* end_io ) (struct nvm_rq*) ;struct pblk* private; int /*<<< orphan*/  opcode; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int NR_PHY_IN_LOG ; 
 int /*<<< orphan*/  NVM_OP_PREAD ; 
 int /*<<< orphan*/  PBLK_READ ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  __pblk_end_io_read (struct pblk*,struct nvm_rq*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 struct bio* bio_clone_fast (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 struct bio* bio_split (struct bio*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  generic_start_io_acct (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct pblk_g_ctx* nvm_rq_to_pdu (struct nvm_rq*) ; 
 struct nvm_rq* pblk_alloc_rqd (struct pblk*,int /*<<< orphan*/ ) ; 
 scalar_t__ pblk_alloc_rqd_meta (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_bio_set ; 
 int /*<<< orphan*/  pblk_end_io_read (struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_end_user_read (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_free_rqd (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_get_lba (struct bio*) ; 
 unsigned int pblk_get_secs (struct bio*) ; 
 unsigned int pblk_read_ppalist_rq (struct pblk*,struct nvm_rq*,struct bio*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pblk_read_rq (struct pblk*,struct nvm_rq*,struct bio*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pblk_submit_io (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ *) ; 

void pblk_submit_read(struct pblk *pblk, struct bio *bio)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct request_queue *q = dev->q;
	sector_t blba = pblk_get_lba(bio);
	unsigned int nr_secs = pblk_get_secs(bio);
	bool from_cache;
	struct pblk_g_ctx *r_ctx;
	struct nvm_rq *rqd;
	struct bio *int_bio, *split_bio;

	generic_start_io_acct(q, REQ_OP_READ, bio_sectors(bio),
			      &pblk->disk->part0);

	rqd = pblk_alloc_rqd(pblk, PBLK_READ);

	rqd->opcode = NVM_OP_PREAD;
	rqd->nr_ppas = nr_secs;
	rqd->private = pblk;
	rqd->end_io = pblk_end_io_read;

	r_ctx = nvm_rq_to_pdu(rqd);
	r_ctx->start_time = jiffies;
	r_ctx->lba = blba;

	if (pblk_alloc_rqd_meta(pblk, rqd)) {
		bio_io_error(bio);
		pblk_free_rqd(pblk, rqd, PBLK_READ);
		return;
	}

	/* Clone read bio to deal internally with:
	 * -read errors when reading from drive
	 * -bio_advance() calls during cache reads
	 */
	int_bio = bio_clone_fast(bio, GFP_KERNEL, &pblk_bio_set);

	if (nr_secs > 1)
		nr_secs = pblk_read_ppalist_rq(pblk, rqd, int_bio, blba,
						&from_cache);
	else
		pblk_read_rq(pblk, rqd, int_bio, blba, &from_cache);

split_retry:
	r_ctx->private = bio; /* original bio */
	rqd->bio = int_bio; /* internal bio */

	if (from_cache && nr_secs == rqd->nr_ppas) {
		/* All data was read from cache, we can complete the IO. */
		pblk_end_user_read(bio, 0);
		atomic_inc(&pblk->inflight_io);
		__pblk_end_io_read(pblk, rqd, false);
	} else if (nr_secs != rqd->nr_ppas) {
		/* The read bio request could be partially filled by the write
		 * buffer, but there are some holes that need to be read from
		 * the drive. In order to handle this, we will use block layer
		 * mechanism to split this request in to smaller ones and make
		 * a chain of it.
		 */
		split_bio = bio_split(bio, nr_secs * NR_PHY_IN_LOG, GFP_KERNEL,
					&pblk_bio_set);
		bio_chain(split_bio, bio);
		generic_make_request(bio);

		/* New bio contains first N sectors of the previous one, so
		 * we can continue to use existing rqd, but we need to shrink
		 * the number of PPAs in it. New bio is also guaranteed that
		 * it contains only either data from cache or from drive, newer
		 * mix of them.
		 */
		bio = split_bio;
		rqd->nr_ppas = nr_secs;
		if (rqd->nr_ppas == 1)
			rqd->ppa_addr = rqd->ppa_list[0];

		/* Recreate int_bio - existing might have some needed internal
		 * fields modified already.
		 */
		bio_put(int_bio);
		int_bio = bio_clone_fast(bio, GFP_KERNEL, &pblk_bio_set);
		goto split_retry;
	} else if (pblk_submit_io(pblk, rqd, NULL)) {
		/* Submitting IO to drive failed, let's report an error */
		rqd->error = -ENODEV;
		pblk_end_io_read(rqd);
	}
}