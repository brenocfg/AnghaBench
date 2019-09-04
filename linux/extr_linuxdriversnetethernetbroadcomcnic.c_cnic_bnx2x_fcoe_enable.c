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
typedef  scalar_t__ u32 ;
struct kwqe {int dummy; } ;
struct fcoe_kwqe_conn_enable_disable {scalar_t__ conn_id; scalar_t__ context_id; } ;
struct fcoe_conn_enable_disable_ramrod_params {int /*<<< orphan*/  enable_disable_kwqe; } ;
struct cnic_local {int dummy; } ;
struct cnic_dev {int /*<<< orphan*/  netdev; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 scalar_t__ BNX2X_FCOE_L5_CID_BASE ; 
 int CNIC_KWQ16_DATA_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FCOE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  FCOE_RAMROD_CMD_ID_ENABLE_CONN ; 
 struct fcoe_conn_enable_disable_ramrod_params* cnic_get_kwqe_16_data (struct cnic_local*,scalar_t__,union l5cm_specific_data*) ; 
 int cnic_submit_kwqe_16 (struct cnic_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,union l5cm_specific_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fcoe_kwqe_conn_enable_disable*,int) ; 
 int /*<<< orphan*/  memset (struct fcoe_conn_enable_disable_ramrod_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cnic_bnx2x_fcoe_enable(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct fcoe_kwqe_conn_enable_disable *req;
	struct fcoe_conn_enable_disable_ramrod_params *fcoe_enable;
	union l5cm_specific_data l5_data;
	int ret;
	u32 cid, l5_cid;
	struct cnic_local *cp = dev->cnic_priv;

	req = (struct fcoe_kwqe_conn_enable_disable *) kwqe;
	cid = req->context_id;
	l5_cid = req->conn_id + BNX2X_FCOE_L5_CID_BASE;

	if (sizeof(*fcoe_enable) > CNIC_KWQ16_DATA_SIZE) {
		netdev_err(dev->netdev, "fcoe_enable size too big\n");
		return -ENOMEM;
	}
	fcoe_enable = cnic_get_kwqe_16_data(cp, l5_cid, &l5_data);
	if (!fcoe_enable)
		return -ENOMEM;

	memset(fcoe_enable, 0, sizeof(*fcoe_enable));
	memcpy(&fcoe_enable->enable_disable_kwqe, req, sizeof(*req));
	ret = cnic_submit_kwqe_16(dev, FCOE_RAMROD_CMD_ID_ENABLE_CONN, cid,
				  FCOE_CONNECTION_TYPE, &l5_data);
	return ret;
}