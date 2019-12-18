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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct slim_msg_txn {scalar_t__ mt; int mc; scalar_t__ dt; int rl; int ec; TYPE_1__* msg; int /*<<< orphan*/  tid; int /*<<< orphan*/ * comp; int /*<<< orphan*/  la; } ;
struct slim_controller {int /*<<< orphan*/  dev; } ;
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int num_bytes; int /*<<< orphan*/ * wbuf; int /*<<< orphan*/ * rbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  SLIM_LA_MGR ; 
 int SLIM_MSGQ_BUF_LEN ; 
 scalar_t__ SLIM_MSG_ASM_FIRST_WORD (int,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SLIM_MSG_DEST_ENUMADDR ; 
 scalar_t__ SLIM_MSG_DEST_LOGICALADDR ; 
 int SLIM_MSG_MC_BEGIN_RECONFIGURATION ; 
#define  SLIM_MSG_MC_CONNECT_SINK 130 
#define  SLIM_MSG_MC_CONNECT_SOURCE 129 
#define  SLIM_MSG_MC_DISCONNECT_PORT 128 
 int SLIM_MSG_MC_RECONFIGURE_NOW ; 
 scalar_t__ SLIM_MSG_MT_CORE ; 
 scalar_t__ SLIM_MSG_MT_DEST_REFERRED_USER ; 
 int SLIM_USR_MC_CONNECT_SINK ; 
 int SLIM_USR_MC_CONNECT_SRC ; 
 int SLIM_USR_MC_DISCONNECT_PORT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct qcom_slim_ngd_ctrl* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__* qcom_slim_ngd_tx_msg_get (struct qcom_slim_ngd_ctrl*,int,int /*<<< orphan*/ *) ; 
 int qcom_slim_ngd_tx_msg_post (struct qcom_slim_ngd_ctrl*,scalar_t__*,int) ; 
 int slim_alloc_txn_tid (struct slim_controller*,struct slim_msg_txn*) ; 
 scalar_t__ slim_ec_txn (scalar_t__,int) ; 
 scalar_t__ slim_tid_txn (scalar_t__,int) ; 
 int /*<<< orphan*/  tx_sent ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_slim_ngd_xfer_msg(struct slim_controller *sctrl,
				  struct slim_msg_txn *txn)
{
	struct qcom_slim_ngd_ctrl *ctrl = dev_get_drvdata(sctrl->dev);
	DECLARE_COMPLETION_ONSTACK(tx_sent);
	DECLARE_COMPLETION_ONSTACK(done);
	int ret, timeout, i;
	u8 wbuf[SLIM_MSGQ_BUF_LEN];
	u8 rbuf[SLIM_MSGQ_BUF_LEN];
	u32 *pbuf;
	u8 *puc;
	u8 la = txn->la;
	bool usr_msg = false;

	if (txn->mt == SLIM_MSG_MT_CORE &&
		(txn->mc >= SLIM_MSG_MC_BEGIN_RECONFIGURATION &&
		 txn->mc <= SLIM_MSG_MC_RECONFIGURE_NOW))
		return 0;

	if (txn->dt == SLIM_MSG_DEST_ENUMADDR)
		return -EPROTONOSUPPORT;

	if (txn->msg->num_bytes > SLIM_MSGQ_BUF_LEN ||
			txn->rl > SLIM_MSGQ_BUF_LEN) {
		dev_err(ctrl->dev, "msg exceeds HW limit\n");
		return -EINVAL;
	}

	pbuf = qcom_slim_ngd_tx_msg_get(ctrl, txn->rl, &tx_sent);
	if (!pbuf) {
		dev_err(ctrl->dev, "Message buffer unavailable\n");
		return -ENOMEM;
	}

	if (txn->mt == SLIM_MSG_MT_CORE &&
		(txn->mc == SLIM_MSG_MC_CONNECT_SOURCE ||
		txn->mc == SLIM_MSG_MC_CONNECT_SINK ||
		txn->mc == SLIM_MSG_MC_DISCONNECT_PORT)) {
		txn->mt = SLIM_MSG_MT_DEST_REFERRED_USER;
		switch (txn->mc) {
		case SLIM_MSG_MC_CONNECT_SOURCE:
			txn->mc = SLIM_USR_MC_CONNECT_SRC;
			break;
		case SLIM_MSG_MC_CONNECT_SINK:
			txn->mc = SLIM_USR_MC_CONNECT_SINK;
			break;
		case SLIM_MSG_MC_DISCONNECT_PORT:
			txn->mc = SLIM_USR_MC_DISCONNECT_PORT;
			break;
		default:
			return -EINVAL;
		}

		usr_msg = true;
		i = 0;
		wbuf[i++] = txn->la;
		la = SLIM_LA_MGR;
		wbuf[i++] = txn->msg->wbuf[0];
		if (txn->mc != SLIM_USR_MC_DISCONNECT_PORT)
			wbuf[i++] = txn->msg->wbuf[1];

		txn->comp = &done;
		ret = slim_alloc_txn_tid(sctrl, txn);
		if (ret) {
			dev_err(ctrl->dev, "Unable to allocate TID\n");
			return ret;
		}

		wbuf[i++] = txn->tid;

		txn->msg->num_bytes = i;
		txn->msg->wbuf = wbuf;
		txn->msg->rbuf = rbuf;
		txn->rl = txn->msg->num_bytes + 4;
	}

	/* HW expects length field to be excluded */
	txn->rl--;
	puc = (u8 *)pbuf;
	*pbuf = 0;
	if (txn->dt == SLIM_MSG_DEST_LOGICALADDR) {
		*pbuf = SLIM_MSG_ASM_FIRST_WORD(txn->rl, txn->mt, txn->mc, 0,
				la);
		puc += 3;
	} else {
		*pbuf = SLIM_MSG_ASM_FIRST_WORD(txn->rl, txn->mt, txn->mc, 1,
				la);
		puc += 2;
	}

	if (slim_tid_txn(txn->mt, txn->mc))
		*(puc++) = txn->tid;

	if (slim_ec_txn(txn->mt, txn->mc)) {
		*(puc++) = (txn->ec & 0xFF);
		*(puc++) = (txn->ec >> 8) & 0xFF;
	}

	if (txn->msg && txn->msg->wbuf)
		memcpy(puc, txn->msg->wbuf, txn->msg->num_bytes);

	ret = qcom_slim_ngd_tx_msg_post(ctrl, pbuf, txn->rl);
	if (ret)
		return ret;

	timeout = wait_for_completion_timeout(&tx_sent, HZ);
	if (!timeout) {
		dev_err(sctrl->dev, "TX timed out:MC:0x%x,mt:0x%x", txn->mc,
					txn->mt);
		return -ETIMEDOUT;
	}

	if (usr_msg) {
		timeout = wait_for_completion_timeout(&done, HZ);
		if (!timeout) {
			dev_err(sctrl->dev, "TX timed out:MC:0x%x,mt:0x%x",
				txn->mc, txn->mt);
			return -ETIMEDOUT;
		}
	}

	return 0;
}