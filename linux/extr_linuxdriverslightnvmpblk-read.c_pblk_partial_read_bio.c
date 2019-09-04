#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pblk {int dummy; } ;
struct nvm_rq {TYPE_1__* bio; int /*<<< orphan*/  end_io; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_vcnt; } ;

/* Variables and functions */
 int NVM_IO_ERR ; 
 int NVM_IO_OK ; 
 int /*<<< orphan*/  __pblk_end_io_read (struct pblk*,struct nvm_rq*,int) ; 
 int /*<<< orphan*/  bio_put (TYPE_1__*) ; 
 int bitmap_weight (unsigned long*,int) ; 
 int /*<<< orphan*/  pblk_bio_free_pages (struct pblk*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_end_partial_read ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 scalar_t__ pblk_setup_partial_read (struct pblk*,struct nvm_rq*,unsigned int,unsigned long*,int) ; 
 int pblk_submit_io (struct pblk*,struct nvm_rq*) ; 

__attribute__((used)) static int pblk_partial_read_bio(struct pblk *pblk, struct nvm_rq *rqd,
				 unsigned int bio_init_idx,
				 unsigned long *read_bitmap, int nr_secs)
{
	int nr_holes;
	int ret;

	nr_holes = nr_secs - bitmap_weight(read_bitmap, nr_secs);

	if (pblk_setup_partial_read(pblk, rqd, bio_init_idx, read_bitmap,
				    nr_holes))
		return NVM_IO_ERR;

	rqd->end_io = pblk_end_partial_read;

	ret = pblk_submit_io(pblk, rqd);
	if (ret) {
		bio_put(rqd->bio);
		pblk_err(pblk, "partial read IO submission failed\n");
		goto err;
	}

	return NVM_IO_OK;

err:
	pblk_err(pblk, "failed to perform partial read\n");

	/* Free allocated pages in new bio */
	pblk_bio_free_pages(pblk, rqd->bio, 0, rqd->bio->bi_vcnt);
	__pblk_end_io_read(pblk, rqd, false);
	return NVM_IO_ERR;
}