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
struct bnx2x {int /*<<< orphan*/  cmng; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_PORT (struct bnx2x*) ; 
 int CMNG_FNS_NONE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  bnx2x_cmng_fns_init (struct bnx2x*,int,int) ; 
 int bnx2x_get_cmng_fns_mode (struct bnx2x*) ; 
 int /*<<< orphan*/  storm_memset_cmng (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bnx2x_set_local_cmng(struct bnx2x *bp)
{
	int cmng_fns = bnx2x_get_cmng_fns_mode(bp);

	if (cmng_fns != CMNG_FNS_NONE) {
		bnx2x_cmng_fns_init(bp, false, cmng_fns);
		storm_memset_cmng(bp, &bp->cmng, BP_PORT(bp));
	} else {
		/* rate shaping and fairness are disabled */
		DP(NETIF_MSG_IFUP,
		   "single function mode without fairness\n");
	}
}