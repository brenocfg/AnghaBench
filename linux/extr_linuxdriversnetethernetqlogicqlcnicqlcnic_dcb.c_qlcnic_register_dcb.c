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
struct qlcnic_dcb {scalar_t__ state; struct qlcnic_adapter* adapter; } ;
struct qlcnic_adapter {struct qlcnic_dcb* dcb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct qlcnic_dcb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_set_dcb_ops (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 

int qlcnic_register_dcb(struct qlcnic_adapter *adapter)
{
	struct qlcnic_dcb *dcb;

	if (qlcnic_sriov_vf_check(adapter))
		return 0;

	dcb = kzalloc(sizeof(struct qlcnic_dcb), GFP_ATOMIC);
	if (!dcb)
		return -ENOMEM;

	adapter->dcb = dcb;
	dcb->adapter = adapter;
	qlcnic_set_dcb_ops(adapter);
	dcb->state = 0;

	return 0;
}