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
struct TYPE_2__ {scalar_t__ instance_state; } ;
struct hnae3_handle {TYPE_1__ rinfo; } ;

/* Variables and functions */
 scalar_t__ HNS_ROCE_STATE_INITED ; 
 scalar_t__ HNS_ROCE_STATE_NON_INIT ; 
 scalar_t__ HNS_ROCE_STATE_UNINIT ; 
 int /*<<< orphan*/  __hns_roce_hw_v2_uninit_instance (struct hnae3_handle*,int) ; 

__attribute__((used)) static void hns_roce_hw_v2_uninit_instance(struct hnae3_handle *handle,
					   bool reset)
{
	if (handle->rinfo.instance_state != HNS_ROCE_STATE_INITED)
		return;

	handle->rinfo.instance_state = HNS_ROCE_STATE_UNINIT;

	__hns_roce_hw_v2_uninit_instance(handle, reset);

	handle->rinfo.instance_state = HNS_ROCE_STATE_NON_INIT;
}