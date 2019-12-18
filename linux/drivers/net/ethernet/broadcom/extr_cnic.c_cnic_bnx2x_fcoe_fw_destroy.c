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
typedef  union l5cm_specific_data {int dummy; } l5cm_specific_data ;
typedef  int /*<<< orphan*/  u32 ;
struct kwqe {int dummy; } ;
struct cnic_local {int /*<<< orphan*/  fcoe_init_cid; } ;
struct cnic_dev {int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  l5_data ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_HW_CID (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCOE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  FCOE_RAMROD_CMD_ID_DESTROY_FUNC ; 
 int /*<<< orphan*/  MAX_ISCSI_TBL_SZ ; 
 int /*<<< orphan*/  cnic_bnx2x_delete_wait (struct cnic_dev*,int /*<<< orphan*/ ) ; 
 int cnic_submit_kwqe_16 (struct cnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union l5cm_specific_data*) ; 
 int /*<<< orphan*/  memset (union l5cm_specific_data*,int /*<<< orphan*/ ,int) ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnic_bnx2x_fcoe_fw_destroy(struct cnic_dev *dev, struct kwqe *kwqe)
{
	union l5cm_specific_data l5_data;
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	int ret;
	u32 cid;

	cnic_bnx2x_delete_wait(dev, MAX_ISCSI_TBL_SZ);

	cid = BNX2X_HW_CID(bp, cp->fcoe_init_cid);

	memset(&l5_data, 0, sizeof(l5_data));
	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_DESTROY_FUNC, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	return ret;
}