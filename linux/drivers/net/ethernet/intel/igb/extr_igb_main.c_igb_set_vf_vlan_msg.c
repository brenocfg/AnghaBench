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
typedef  size_t u32 ;
struct igb_adapter {TYPE_1__* vf_data; } ;
struct TYPE_2__ {scalar_t__ pf_vlan; } ;

/* Variables and functions */
 size_t E1000_VLVF_VLANID_MASK ; 
 size_t E1000_VT_MSGINFO_MASK ; 
 size_t E1000_VT_MSGINFO_SHIFT ; 
 int igb_set_vf_vlan (struct igb_adapter*,int,int,size_t) ; 
 int /*<<< orphan*/  igb_set_vf_vlan_strip (struct igb_adapter*,size_t,int) ; 

__attribute__((used)) static int igb_set_vf_vlan_msg(struct igb_adapter *adapter, u32 *msgbuf, u32 vf)
{
	int add = (msgbuf[0] & E1000_VT_MSGINFO_MASK) >> E1000_VT_MSGINFO_SHIFT;
	int vid = (msgbuf[1] & E1000_VLVF_VLANID_MASK);
	int ret;

	if (adapter->vf_data[vf].pf_vlan)
		return -1;

	/* VLAN 0 is a special case, don't allow it to be removed */
	if (!vid && !add)
		return 0;

	ret = igb_set_vf_vlan(adapter, vid, !!add, vf);
	if (!ret)
		igb_set_vf_vlan_strip(adapter, vf, !!vid);
	return ret;
}