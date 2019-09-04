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
struct tc_cls_u32_offload {int command; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSU32_DELETE_KNODE 130 
#define  TC_CLSU32_NEW_KNODE 129 
#define  TC_CLSU32_REPLACE_KNODE 128 
 int cxgb4_config_knode (struct net_device*,struct tc_cls_u32_offload*) ; 
 int cxgb4_delete_knode (struct net_device*,struct tc_cls_u32_offload*) ; 

__attribute__((used)) static int cxgb_setup_tc_cls_u32(struct net_device *dev,
				 struct tc_cls_u32_offload *cls_u32)
{
	switch (cls_u32->command) {
	case TC_CLSU32_NEW_KNODE:
	case TC_CLSU32_REPLACE_KNODE:
		return cxgb4_config_knode(dev, cls_u32);
	case TC_CLSU32_DELETE_KNODE:
		return cxgb4_delete_knode(dev, cls_u32);
	default:
		return -EOPNOTSUPP;
	}
}