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
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_config_rss_params {int /*<<< orphan*/  ramrod_flags; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int bnx2x_config_rss (struct bnx2x*,struct bnx2x_config_rss_params*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2x_vf_rss_update(struct bnx2x *bp, struct bnx2x_virtf *vf,
			struct bnx2x_config_rss_params *rss)
{
	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->abs_vfid);
	set_bit(RAMROD_COMP_WAIT, &rss->ramrod_flags);
	return bnx2x_config_rss(bp, rss);
}