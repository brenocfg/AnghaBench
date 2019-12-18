#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  reset_state; int /*<<< orphan*/  state; } ;
struct hnae3_handle {TYPE_2__* pdev; TYPE_1__ rinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_RST_DIRECT_RETURN ; 
 int /*<<< orphan*/  HNS_ROCE_STATE_RST_UNINIT ; 
 int /*<<< orphan*/  HNS_ROCE_V2_HW_RST_UNINT_DELAY ; 
 int /*<<< orphan*/  __hns_roce_hw_v2_uninit_instance (struct hnae3_handle*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_roce_hw_v2_reset_notify_uninit(struct hnae3_handle *handle)
{
	if (test_bit(HNS_ROCE_RST_DIRECT_RETURN, &handle->rinfo.state))
		return 0;

	handle->rinfo.reset_state = HNS_ROCE_STATE_RST_UNINIT;
	dev_info(&handle->pdev->dev, "In reset process RoCE client uninit.\n");
	msleep(HNS_ROCE_V2_HW_RST_UNINT_DELAY);
	__hns_roce_hw_v2_uninit_instance(handle, false);

	return 0;
}