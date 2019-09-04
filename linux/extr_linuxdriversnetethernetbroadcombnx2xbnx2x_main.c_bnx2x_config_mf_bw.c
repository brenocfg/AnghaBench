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
struct TYPE_2__ {scalar_t__ link_up; } ;
struct bnx2x {int /*<<< orphan*/  cmng; TYPE_1__ link_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  CMNG_FNS_MINMAX ; 
 int /*<<< orphan*/  bnx2x_cmng_fns_init (struct bnx2x*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_link_sync_notify (struct bnx2x*) ; 
 int /*<<< orphan*/  storm_memset_cmng (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_config_mf_bw(struct bnx2x *bp)
{
	if (bp->link_vars.link_up) {
		bnx2x_cmng_fns_init(bp, true, CMNG_FNS_MINMAX);
		bnx2x_link_sync_notify(bp);
	}
	storm_memset_cmng(bp, &bp->cmng, BP_PORT(bp));
}