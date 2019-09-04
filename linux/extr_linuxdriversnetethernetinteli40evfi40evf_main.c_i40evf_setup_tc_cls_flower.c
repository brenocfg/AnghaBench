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
struct TYPE_2__ {scalar_t__ chain_index; } ;
struct tc_cls_flower_offload {int command; TYPE_1__ common; } ;
struct i40evf_adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSFLOWER_DESTROY 130 
#define  TC_CLSFLOWER_REPLACE 129 
#define  TC_CLSFLOWER_STATS 128 
 int i40evf_configure_clsflower (struct i40evf_adapter*,struct tc_cls_flower_offload*) ; 
 int i40evf_delete_clsflower (struct i40evf_adapter*,struct tc_cls_flower_offload*) ; 

__attribute__((used)) static int i40evf_setup_tc_cls_flower(struct i40evf_adapter *adapter,
				      struct tc_cls_flower_offload *cls_flower)
{
	if (cls_flower->common.chain_index)
		return -EOPNOTSUPP;

	switch (cls_flower->command) {
	case TC_CLSFLOWER_REPLACE:
		return i40evf_configure_clsflower(adapter, cls_flower);
	case TC_CLSFLOWER_DESTROY:
		return i40evf_delete_clsflower(adapter, cls_flower);
	case TC_CLSFLOWER_STATS:
		return -EOPNOTSUPP;
	default:
		return -EOPNOTSUPP;
	}
}