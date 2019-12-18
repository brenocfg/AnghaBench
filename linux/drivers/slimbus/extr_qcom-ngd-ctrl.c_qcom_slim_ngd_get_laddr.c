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
typedef  scalar_t__ u8 ;
struct slim_val_inf {int num_bytes; scalar_t__* rbuf; scalar_t__* wbuf; int /*<<< orphan*/  member_0; } ;
struct slim_msg_txn {int rl; scalar_t__ tid; struct slim_val_inf* msg; int /*<<< orphan*/  mc; scalar_t__ ec; int /*<<< orphan*/  la; int /*<<< orphan*/  dt; int /*<<< orphan*/  mt; } ;
struct slim_eaddr {int dummy; } ;
struct slim_controller {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SLIM_LA_MGR ; 
 int /*<<< orphan*/  SLIM_MSG_DEST_LOGICALADDR ; 
 int /*<<< orphan*/  SLIM_MSG_MT_DEST_REFERRED_USER ; 
 int /*<<< orphan*/  SLIM_USR_MC_ADDR_QUERY ; 
 int /*<<< orphan*/  memcmp (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,struct slim_eaddr*,int) ; 
 int qcom_slim_ngd_xfer_msg_sync (struct slim_controller*,struct slim_msg_txn*) ; 
 int slim_alloc_txn_tid (struct slim_controller*,struct slim_msg_txn*) ; 
 int /*<<< orphan*/  slim_free_txn_tid (struct slim_controller*,struct slim_msg_txn*) ; 

__attribute__((used)) static int qcom_slim_ngd_get_laddr(struct slim_controller *ctrl,
				   struct slim_eaddr *ea, u8 *laddr)
{
	struct slim_val_inf msg =  {0};
	u8 failed_ea[6] = {0, 0, 0, 0, 0, 0};
	struct slim_msg_txn txn;
	u8 wbuf[10] = {0};
	u8 rbuf[10] = {0};
	int ret;

	txn.mt = SLIM_MSG_MT_DEST_REFERRED_USER;
	txn.dt = SLIM_MSG_DEST_LOGICALADDR;
	txn.la = SLIM_LA_MGR;
	txn.ec = 0;

	txn.mc = SLIM_USR_MC_ADDR_QUERY;
	txn.rl = 11;
	txn.msg = &msg;
	txn.msg->num_bytes = 7;
	txn.msg->wbuf = wbuf;
	txn.msg->rbuf = rbuf;

	ret = slim_alloc_txn_tid(ctrl, &txn);
	if (ret < 0)
		return ret;

	wbuf[0] = (u8)txn.tid;
	memcpy(&wbuf[1], ea, sizeof(*ea));

	ret = qcom_slim_ngd_xfer_msg_sync(ctrl, &txn);
	if (ret) {
		slim_free_txn_tid(ctrl, &txn);
		return ret;
	}

	if (!memcmp(rbuf, failed_ea, 6))
		return -ENXIO;

	*laddr = rbuf[6];

	return ret;
}