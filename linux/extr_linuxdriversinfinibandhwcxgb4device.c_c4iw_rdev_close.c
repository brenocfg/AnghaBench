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
struct c4iw_rdev {int /*<<< orphan*/  resource; int /*<<< orphan*/  free_workq; int /*<<< orphan*/  rqt_compl; int /*<<< orphan*/  pbl_compl; scalar_t__ status_page; int /*<<< orphan*/  uctx; int /*<<< orphan*/  wr_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_destroy_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c4iw_ocqp_pool_destroy (struct c4iw_rdev*) ; 
 int /*<<< orphan*/  c4iw_pblpool_destroy (struct c4iw_rdev*) ; 
 int /*<<< orphan*/  c4iw_release_dev_ucontext (struct c4iw_rdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c4iw_rqtpool_destroy (struct c4iw_rdev*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void c4iw_rdev_close(struct c4iw_rdev *rdev)
{
	kfree(rdev->wr_log);
	c4iw_release_dev_ucontext(rdev, &rdev->uctx);
	free_page((unsigned long)rdev->status_page);
	c4iw_pblpool_destroy(rdev);
	c4iw_rqtpool_destroy(rdev);
	wait_for_completion(&rdev->pbl_compl);
	wait_for_completion(&rdev->rqt_compl);
	c4iw_ocqp_pool_destroy(rdev);
	destroy_workqueue(rdev->free_workq);
	c4iw_destroy_resource(&rdev->resource);
}