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
typedef  int /*<<< orphan*/  u16 ;
struct tc_cls_flower_offload {int command; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_CLSFLOWER_DESTROY 130 
#define  TC_CLSFLOWER_REPLACE 129 
#define  TC_CLSFLOWER_STATS 128 
 int bnxt_tc_add_flow (struct bnxt*,int /*<<< orphan*/ ,struct tc_cls_flower_offload*) ; 
 int bnxt_tc_del_flow (struct bnxt*,struct tc_cls_flower_offload*) ; 
 int bnxt_tc_get_flow_stats (struct bnxt*,struct tc_cls_flower_offload*) ; 

int bnxt_tc_setup_flower(struct bnxt *bp, u16 src_fid,
			 struct tc_cls_flower_offload *cls_flower)
{
	switch (cls_flower->command) {
	case TC_CLSFLOWER_REPLACE:
		return bnxt_tc_add_flow(bp, src_fid, cls_flower);
	case TC_CLSFLOWER_DESTROY:
		return bnxt_tc_del_flow(bp, cls_flower);
	case TC_CLSFLOWER_STATS:
		return bnxt_tc_get_flow_stats(bp, cls_flower);
	default:
		return -EOPNOTSUPP;
	}
}