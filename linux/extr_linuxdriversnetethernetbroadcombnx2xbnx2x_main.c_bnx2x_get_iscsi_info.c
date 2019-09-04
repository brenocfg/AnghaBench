#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int max_iscsi_conn; } ;
struct bnx2x {int flags; TYPE_1__ cnic_eth_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_iscsi_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*,int) ; 
 int BNX2X_MAX_ISCSI_INIT_CONN_MASK ; 
 int BNX2X_MAX_ISCSI_INIT_CONN_SHIFT ; 
 int BP_PORT (struct bnx2x*) ; 
 int /*<<< orphan*/  CNIC_SUPPORT (struct bnx2x*) ; 
 int FW_ENCODE_32BIT_PATTERN ; 
 int NO_ISCSI_FLAG ; 
 int SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 TYPE_2__* drv_lic_key ; 

void bnx2x_get_iscsi_info(struct bnx2x *bp)
{
	u32 no_flags = NO_ISCSI_FLAG;
	int port = BP_PORT(bp);
	u32 max_iscsi_conn = FW_ENCODE_32BIT_PATTERN ^ SHMEM_RD(bp,
				drv_lic_key[port].max_iscsi_conn);

	if (!CNIC_SUPPORT(bp)) {
		bp->flags |= no_flags;
		return;
	}

	/* Get the number of maximum allowed iSCSI connections */
	bp->cnic_eth_dev.max_iscsi_conn =
		(max_iscsi_conn & BNX2X_MAX_ISCSI_INIT_CONN_MASK) >>
		BNX2X_MAX_ISCSI_INIT_CONN_SHIFT;

	BNX2X_DEV_INFO("max_iscsi_conn 0x%x\n",
		       bp->cnic_eth_dev.max_iscsi_conn);

	/*
	 * If maximum allowed number of connections is zero -
	 * disable the feature.
	 */
	if (!bp->cnic_eth_dev.max_iscsi_conn)
		bp->flags |= no_flags;
}