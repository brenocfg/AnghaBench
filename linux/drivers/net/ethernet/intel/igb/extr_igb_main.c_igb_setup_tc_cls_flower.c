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
struct igb_adapter {int dummy; } ;
struct flow_cls_offload {int command; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  FLOW_CLS_DESTROY 130 
#define  FLOW_CLS_REPLACE 129 
#define  FLOW_CLS_STATS 128 
 int igb_configure_clsflower (struct igb_adapter*,struct flow_cls_offload*) ; 
 int igb_delete_clsflower (struct igb_adapter*,struct flow_cls_offload*) ; 

__attribute__((used)) static int igb_setup_tc_cls_flower(struct igb_adapter *adapter,
				   struct flow_cls_offload *cls_flower)
{
	switch (cls_flower->command) {
	case FLOW_CLS_REPLACE:
		return igb_configure_clsflower(adapter, cls_flower);
	case FLOW_CLS_DESTROY:
		return igb_delete_clsflower(adapter, cls_flower);
	case FLOW_CLS_STATS:
		return -EOPNOTSUPP;
	default:
		return -EOPNOTSUPP;
	}
}