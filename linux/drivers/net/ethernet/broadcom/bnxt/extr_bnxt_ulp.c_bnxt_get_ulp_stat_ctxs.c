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
struct bnxt {int /*<<< orphan*/  edev; } ;

/* Variables and functions */
 int BNXT_MIN_ROCE_STAT_CTXS ; 
 int /*<<< orphan*/  BNXT_ROCE_ULP ; 
 scalar_t__ bnxt_ulp_registered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bnxt_get_ulp_stat_ctxs(struct bnxt *bp)
{
	if (bnxt_ulp_registered(bp->edev, BNXT_ROCE_ULP))
		return BNXT_MIN_ROCE_STAT_CTXS;

	return 0;
}