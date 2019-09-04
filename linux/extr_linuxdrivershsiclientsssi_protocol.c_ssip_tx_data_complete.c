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
struct ssi_protocol {int /*<<< orphan*/  lock; int /*<<< orphan*/  txqueue; } ;
struct hsi_msg {scalar_t__ status; int /*<<< orphan*/  complete; struct hsi_client* cl; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ HSI_STATUS_ERROR ; 
 int /*<<< orphan*/  SENDING_SWBREAK ; 
 int /*<<< orphan*/  SSIP_SWBREAK_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hsi_async_write (struct hsi_client*,struct hsi_msg*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct hsi_msg* ssip_claim_cmd (struct ssi_protocol*) ; 
 int /*<<< orphan*/  ssip_error (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_free_data (struct hsi_msg*) ; 
 int /*<<< orphan*/  ssip_set_cmd (struct hsi_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_set_txstate (struct ssi_protocol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_swbreak_complete ; 
 int /*<<< orphan*/  ssip_xmit (struct hsi_client*) ; 

__attribute__((used)) static void ssip_tx_data_complete(struct hsi_msg *msg)
{
	struct hsi_client *cl = msg->cl;
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	struct hsi_msg *cmsg;

	if (msg->status == HSI_STATUS_ERROR) {
		dev_err(&cl->device, "TX data error\n");
		ssip_error(cl);
		goto out;
	}
	spin_lock_bh(&ssi->lock);
	if (list_empty(&ssi->txqueue)) {
		ssip_set_txstate(ssi, SENDING_SWBREAK);
		spin_unlock_bh(&ssi->lock);
		cmsg = ssip_claim_cmd(ssi);
		ssip_set_cmd(cmsg, SSIP_SWBREAK_CMD);
		cmsg->complete = ssip_swbreak_complete;
		dev_dbg(&cl->device, "Send SWBREAK\n");
		hsi_async_write(cl, cmsg);
	} else {
		spin_unlock_bh(&ssi->lock);
		ssip_xmit(cl);
	}
out:
	ssip_free_data(msg);
}