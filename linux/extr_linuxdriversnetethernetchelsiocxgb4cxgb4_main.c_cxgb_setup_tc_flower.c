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
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSFLOWER_DESTROY 130 
#define  TC_CLSFLOWER_REPLACE 129 
#define  TC_CLSFLOWER_STATS 128 
 int cxgb4_tc_flower_destroy (struct net_device*,struct tc_cls_flower_offload*) ; 
 int cxgb4_tc_flower_replace (struct net_device*,struct tc_cls_flower_offload*) ; 
 int cxgb4_tc_flower_stats (struct net_device*,struct tc_cls_flower_offload*) ; 

__attribute__((used)) static int cxgb_setup_tc_flower(struct net_device *dev,
				struct tc_cls_flower_offload *cls_flower)
{
	switch (cls_flower->command) {
	case TC_CLSFLOWER_REPLACE:
		return cxgb4_tc_flower_replace(dev, cls_flower);
	case TC_CLSFLOWER_DESTROY:
		return cxgb4_tc_flower_destroy(dev, cls_flower);
	case TC_CLSFLOWER_STATS:
		return cxgb4_tc_flower_stats(dev, cls_flower);
	default:
		return -EOPNOTSUPP;
	}
}