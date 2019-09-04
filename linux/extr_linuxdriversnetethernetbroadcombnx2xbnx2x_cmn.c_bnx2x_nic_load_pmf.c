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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int pmf; } ;
struct bnx2x {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_COMMON ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_COMMON_CHIP ; 
 scalar_t__ FW_MSG_CODE_DRV_LOAD_PORT ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void bnx2x_nic_load_pmf(struct bnx2x *bp, u32 load_code)
{
	if ((load_code == FW_MSG_CODE_DRV_LOAD_COMMON) ||
	    (load_code == FW_MSG_CODE_DRV_LOAD_COMMON_CHIP) ||
	    (load_code == FW_MSG_CODE_DRV_LOAD_PORT)) {
		bp->port.pmf = 1;
		/* We need the barrier to ensure the ordering between the
		 * writing to bp->port.pmf here and reading it from the
		 * bnx2x_periodic_task().
		 */
		smp_mb();
	} else {
		bp->port.pmf = 0;
	}

	DP(NETIF_MSG_LINK, "pmf %d\n", bp->port.pmf);
}