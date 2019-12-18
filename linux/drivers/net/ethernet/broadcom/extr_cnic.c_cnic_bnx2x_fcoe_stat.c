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
struct fcoe_stat_ramrod_params {int /*<<< orphan*/  stat_kwqe; } ;
struct fcoe_kwqe_stat {int dummy; } ;
struct cnic_local {int /*<<< orphan*/  fcoe_init_cid; } ;
struct cnic_dev {int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FCOE_L5_CID_BASE ; 
 int /*<<< orphan*/  BNX2X_HW_CID (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FCOE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  FCOE_RAMROD_CMD_ID_STAT_FUNC ; 
 struct fcoe_stat_ramrod_params* cnic_get_kwqe_16_data (struct cnic_local*,int /*<<< orphan*/ ,union l5cm_specific_data*) ; 
 int cnic_submit_kwqe_16 (struct cnic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union l5cm_specific_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fcoe_kwqe_stat*,int) ; 
 int /*<<< orphan*/  memset (struct fcoe_stat_ramrod_params*,int /*<<< orphan*/ ,int) ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnic_bnx2x_fcoe_stat(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct fcoe_kwqe_stat *req;
	struct fcoe_stat_ramrod_params *fcoe_stat;
	union l5cm_specific_data l5_data;
	struct cnic_local *cp = dev->cnic_priv;
	struct bnx2x *bp = netdev_priv(dev->netdev);
	int ret;
	u32 cid;

	req = (struct fcoe_kwqe_stat *) kwqe;
	cid = BNX2X_HW_CID(bp, cp->fcoe_init_cid);

	fcoe_stat = cnic_get_kwqe_16_data(cp, BNX2X_FCOE_L5_CID_BASE, &l5_data);
	if (!fcoe_stat)
		return -ENOMEM;

	memset(fcoe_stat, 0, sizeof(*fcoe_stat));
	memcpy(&fcoe_stat->stat_kwqe, req, sizeof(*req));

	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_STAT_FUNC, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	return ret;
}