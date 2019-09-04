#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bnx2x {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  valid_dump; int /*<<< orphan*/  fw_ver; int /*<<< orphan*/  drv_ver; int /*<<< orphan*/  epoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRV_MODULE_VERSION ; 
 int FIRST_DUMP_VALID ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int SECOND_DUMP_VALID ; 
 int /*<<< orphan*/  SHMEM2_HAS (struct bnx2x*,TYPE_1__) ; 
 int SHMEM2_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSEM_REG_PRAM ; 
 int bnx2x_update_mng_version_utility (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ drv_info ; 
 scalar_t__ ktime_get_real_seconds () ; 

void bnx2x_update_mfw_dump(struct bnx2x *bp)
{
	u32 drv_ver;
	u32 valid_dump;

	if (!SHMEM2_HAS(bp, drv_info))
		return;

	/* Update Driver load time, possibly broken in y2038 */
	SHMEM2_WR(bp, drv_info.epoc, (u32)ktime_get_real_seconds());

	drv_ver = bnx2x_update_mng_version_utility(DRV_MODULE_VERSION, true);
	SHMEM2_WR(bp, drv_info.drv_ver, drv_ver);

	SHMEM2_WR(bp, drv_info.fw_ver, REG_RD(bp, XSEM_REG_PRAM));

	/* Check & notify On-Chip dump. */
	valid_dump = SHMEM2_RD(bp, drv_info.valid_dump);

	if (valid_dump & FIRST_DUMP_VALID)
		DP(NETIF_MSG_IFUP, "A valid On-Chip MFW dump found on 1st partition\n");

	if (valid_dump & SECOND_DUMP_VALID)
		DP(NETIF_MSG_IFUP, "A valid On-Chip MFW dump found on 2nd partition\n");
}