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
struct net_device {int dummy; } ;
struct flow_cls_offload {int command; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  FLOW_CLS_DESTROY 130 
#define  FLOW_CLS_REPLACE 129 
#define  FLOW_CLS_STATS 128 
 int cxgb4_tc_flower_destroy (struct net_device*,struct flow_cls_offload*) ; 
 int cxgb4_tc_flower_replace (struct net_device*,struct flow_cls_offload*) ; 
 int cxgb4_tc_flower_stats (struct net_device*,struct flow_cls_offload*) ; 

__attribute__((used)) static int cxgb_setup_tc_flower(struct net_device *dev,
				struct flow_cls_offload *cls_flower)
{
	switch (cls_flower->command) {
	case FLOW_CLS_REPLACE:
		return cxgb4_tc_flower_replace(dev, cls_flower);
	case FLOW_CLS_DESTROY:
		return cxgb4_tc_flower_destroy(dev, cls_flower);
	case FLOW_CLS_STATS:
		return cxgb4_tc_flower_stats(dev, cls_flower);
	default:
		return -EOPNOTSUPP;
	}
}