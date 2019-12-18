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
struct pvrdma_dev {int dummy; } ;
struct pvrdma_cq {int /*<<< orphan*/  pdir; int /*<<< orphan*/  umem; int /*<<< orphan*/  free; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_page_dir_cleanup (struct pvrdma_dev*,int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvrdma_free_cq(struct pvrdma_dev *dev, struct pvrdma_cq *cq)
{
	if (refcount_dec_and_test(&cq->refcnt))
		complete(&cq->free);
	wait_for_completion(&cq->free);

	ib_umem_release(cq->umem);

	pvrdma_page_dir_cleanup(dev, &cq->pdir);
}