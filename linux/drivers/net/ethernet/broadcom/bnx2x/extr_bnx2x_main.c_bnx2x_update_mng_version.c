#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union drv_info_to_mcp {int dummy; } drv_info_to_mcp ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {scalar_t__ state; int /*<<< orphan*/  drv_info_mutex; TYPE_3__* slowpath; scalar_t__ drv_info_mng_owner; } ;
struct TYPE_11__ {int /*<<< orphan*/ * versions; } ;
struct TYPE_8__ {int /*<<< orphan*/ * version; } ;
struct TYPE_7__ {int /*<<< orphan*/ * version; } ;
struct TYPE_10__ {TYPE_2__ fcoe_stat; TYPE_1__ iscsi_stat; } ;
struct TYPE_9__ {TYPE_4__ drv_info_to_mcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_MCP ; 
 scalar_t__ BNX2X_STATE_OPEN ; 
 int BP_FW_MB_IDX (struct bnx2x*) ; 
 int /*<<< orphan*/  CNIC_LOADED (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DRV_MODULE_VERSION ; 
 size_t DRV_PERS_ETHERNET ; 
 size_t DRV_PERS_FCOE ; 
 size_t DRV_PERS_ISCSI ; 
 int /*<<< orphan*/  DRV_VER_NOT_LOADED ; 
 int /*<<< orphan*/  SHMEM2_HAS (struct bnx2x*,TYPE_5__*) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_drv_info_fcoe_stat (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_drv_info_iscsi_stat (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_update_mng_version_utility (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* func_os_drv_ver ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void bnx2x_update_mng_version(struct bnx2x *bp)
{
	u32 iscsiver = DRV_VER_NOT_LOADED;
	u32 fcoever = DRV_VER_NOT_LOADED;
	u32 ethver = DRV_VER_NOT_LOADED;
	int idx = BP_FW_MB_IDX(bp);
	u8 *version;

	if (!SHMEM2_HAS(bp, func_os_drv_ver))
		return;

	mutex_lock(&bp->drv_info_mutex);
	/* Must not proceed when `bnx2x_handle_drv_info_req' is feasible */
	if (bp->drv_info_mng_owner)
		goto out;

	if (bp->state != BNX2X_STATE_OPEN)
		goto out;

	/* Parse ethernet driver version */
	ethver = bnx2x_update_mng_version_utility(DRV_MODULE_VERSION, true);
	if (!CNIC_LOADED(bp))
		goto out;

	/* Try getting storage driver version via cnic */
	memset(&bp->slowpath->drv_info_to_mcp, 0,
	       sizeof(union drv_info_to_mcp));
	bnx2x_drv_info_iscsi_stat(bp);
	version = bp->slowpath->drv_info_to_mcp.iscsi_stat.version;
	iscsiver = bnx2x_update_mng_version_utility(version, false);

	memset(&bp->slowpath->drv_info_to_mcp, 0,
	       sizeof(union drv_info_to_mcp));
	bnx2x_drv_info_fcoe_stat(bp);
	version = bp->slowpath->drv_info_to_mcp.fcoe_stat.version;
	fcoever = bnx2x_update_mng_version_utility(version, false);

out:
	SHMEM2_WR(bp, func_os_drv_ver[idx].versions[DRV_PERS_ETHERNET], ethver);
	SHMEM2_WR(bp, func_os_drv_ver[idx].versions[DRV_PERS_ISCSI], iscsiver);
	SHMEM2_WR(bp, func_os_drv_ver[idx].versions[DRV_PERS_FCOE], fcoever);

	mutex_unlock(&bp->drv_info_mutex);

	DP(BNX2X_MSG_MCP, "Setting driver version: ETH [%08x] iSCSI [%08x] FCoE [%08x]\n",
	   ethver, iscsiver, fcoever);
}