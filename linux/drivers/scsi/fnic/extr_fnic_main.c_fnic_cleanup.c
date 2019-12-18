#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fnic {unsigned int intr_count; unsigned int rq_count; unsigned int raw_wq_count; unsigned int wq_copy_count; unsigned int cq_count; int /*<<< orphan*/ * io_sgl_pool; int /*<<< orphan*/  io_req_pool; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * wq_copy; int /*<<< orphan*/ * rq; int /*<<< orphan*/ * wq; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 unsigned int FNIC_SGL_NUM_CACHES ; 
 int /*<<< orphan*/  fnic_free_rq_buf ; 
 int /*<<< orphan*/  fnic_free_wq_buf ; 
 int /*<<< orphan*/  fnic_rq_cmpl_handler (struct fnic*,int) ; 
 int /*<<< orphan*/  fnic_wq_cmpl_handler (struct fnic*,int) ; 
 int /*<<< orphan*/  fnic_wq_copy_cleanup_handler ; 
 int /*<<< orphan*/  fnic_wq_copy_cmpl_handler (struct fnic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_completions ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_cq_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_dev_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_intr_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_rq_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vnic_rq_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_wq_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_wq_copy_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vnic_wq_copy_disable (int /*<<< orphan*/ *) ; 
 int vnic_wq_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fnic_cleanup(struct fnic *fnic)
{
	unsigned int i;
	int err;

	vnic_dev_disable(fnic->vdev);
	for (i = 0; i < fnic->intr_count; i++)
		vnic_intr_mask(&fnic->intr[i]);

	for (i = 0; i < fnic->rq_count; i++) {
		err = vnic_rq_disable(&fnic->rq[i]);
		if (err)
			return err;
	}
	for (i = 0; i < fnic->raw_wq_count; i++) {
		err = vnic_wq_disable(&fnic->wq[i]);
		if (err)
			return err;
	}
	for (i = 0; i < fnic->wq_copy_count; i++) {
		err = vnic_wq_copy_disable(&fnic->wq_copy[i]);
		if (err)
			return err;
	}

	/* Clean up completed IOs and FCS frames */
	fnic_wq_copy_cmpl_handler(fnic, io_completions);
	fnic_wq_cmpl_handler(fnic, -1);
	fnic_rq_cmpl_handler(fnic, -1);

	/* Clean up the IOs and FCS frames that have not completed */
	for (i = 0; i < fnic->raw_wq_count; i++)
		vnic_wq_clean(&fnic->wq[i], fnic_free_wq_buf);
	for (i = 0; i < fnic->rq_count; i++)
		vnic_rq_clean(&fnic->rq[i], fnic_free_rq_buf);
	for (i = 0; i < fnic->wq_copy_count; i++)
		vnic_wq_copy_clean(&fnic->wq_copy[i],
				   fnic_wq_copy_cleanup_handler);

	for (i = 0; i < fnic->cq_count; i++)
		vnic_cq_clean(&fnic->cq[i]);
	for (i = 0; i < fnic->intr_count; i++)
		vnic_intr_clean(&fnic->intr[i]);

	mempool_destroy(fnic->io_req_pool);
	for (i = 0; i < FNIC_SGL_NUM_CACHES; i++)
		mempool_destroy(fnic->io_sgl_pool[i]);

	return 0;
}