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
struct bnxt {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_close_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  bnxt_dbg_dump_states (struct bnxt*) ; 
 int bnxt_open_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  bnxt_ulp_start (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_ulp_stop (struct bnxt*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_reset_task(struct bnxt *bp, bool silent)
{
	if (!silent)
		bnxt_dbg_dump_states(bp);
	if (netif_running(bp->dev)) {
		int rc;

		if (!silent)
			bnxt_ulp_stop(bp);
		bnxt_close_nic(bp, false, false);
		rc = bnxt_open_nic(bp, false, false);
		if (!silent && !rc)
			bnxt_ulp_start(bp);
	}
}