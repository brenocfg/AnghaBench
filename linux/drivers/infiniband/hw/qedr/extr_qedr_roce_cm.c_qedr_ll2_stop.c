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
struct qedr_dev {scalar_t__ gsi_ll2_handle; int /*<<< orphan*/  rdma_ctx; TYPE_1__* ops; int /*<<< orphan*/  gsi_ll2_mac_address; int /*<<< orphan*/  cdev; } ;
struct TYPE_2__ {int (* ll2_set_mac_filter ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* ll2_terminate_connection ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* ll2_release_connection ) (int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int) ; 
 scalar_t__ QED_LL2_UNUSED_HANDLE ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int qedr_ll2_stop(struct qedr_dev *dev)
{
	int rc;

	if (dev->gsi_ll2_handle == QED_LL2_UNUSED_HANDLE)
		return 0;

	/* remove LL2 MAC address filter */
	rc = dev->ops->ll2_set_mac_filter(dev->cdev,
					  dev->gsi_ll2_mac_address, NULL);

	rc = dev->ops->ll2_terminate_connection(dev->rdma_ctx,
						dev->gsi_ll2_handle);
	if (rc)
		DP_ERR(dev, "Failed to terminate LL2 connection (rc=%d)\n", rc);

	dev->ops->ll2_release_connection(dev->rdma_ctx, dev->gsi_ll2_handle);

	dev->gsi_ll2_handle = QED_LL2_UNUSED_HANDLE;

	return rc;
}