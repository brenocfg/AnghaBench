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
struct tc_cls_flower_offload {int command; } ;
struct igb_adapter {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSFLOWER_DESTROY 130 
#define  TC_CLSFLOWER_REPLACE 129 
#define  TC_CLSFLOWER_STATS 128 
 int igb_configure_clsflower (struct igb_adapter*,struct tc_cls_flower_offload*) ; 
 int igb_delete_clsflower (struct igb_adapter*,struct tc_cls_flower_offload*) ; 

__attribute__((used)) static int igb_setup_tc_cls_flower(struct igb_adapter *adapter,
				   struct tc_cls_flower_offload *cls_flower)
{
	switch (cls_flower->command) {
	case TC_CLSFLOWER_REPLACE:
		return igb_configure_clsflower(adapter, cls_flower);
	case TC_CLSFLOWER_DESTROY:
		return igb_delete_clsflower(adapter, cls_flower);
	case TC_CLSFLOWER_STATS:
		return -EOPNOTSUPP;
	default:
		return -EOPNOTSUPP;
	}
}