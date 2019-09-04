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
struct hnae3_handle {TYPE_1__* pdev; int /*<<< orphan*/ * priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hns_roce_hw_v2_init_instance (struct hnae3_handle*) ; 

__attribute__((used)) static int hns_roce_hw_v2_reset_notify_init(struct hnae3_handle *handle)
{
	int ret;

	ret = hns_roce_hw_v2_init_instance(handle);
	if (ret) {
		/* when reset notify type is HNAE3_INIT_CLIENT In reset notify
		 * callback function, RoCE Engine reinitialize. If RoCE reinit
		 * failed, we should inform NIC driver.
		 */
		handle->priv = NULL;
		dev_err(&handle->pdev->dev,
			"In reset process RoCE reinit failed %d.\n", ret);
	}

	return ret;
}