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
struct ssi_protocol {scalar_t__ main_state; scalar_t__ recv_state; int /*<<< orphan*/  lock; } ;
struct hsi_msg {int /*<<< orphan*/  complete; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ ACTIVE ; 
 scalar_t__ RECV_READY ; 
 int /*<<< orphan*/  SSIP_READY_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  hsi_async_write (struct hsi_client*,struct hsi_msg*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct hsi_msg* ssip_claim_cmd (struct ssi_protocol*) ; 
 int /*<<< orphan*/  ssip_release_cmd ; 
 int /*<<< orphan*/  ssip_set_cmd (struct hsi_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_set_rxstate (struct ssi_protocol*,scalar_t__) ; 

__attribute__((used)) static void ssip_start_rx(struct hsi_client *cl)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	struct hsi_msg *msg;

	dev_dbg(&cl->device, "RX start M(%d) R(%d)\n", ssi->main_state,
						ssi->recv_state);
	spin_lock_bh(&ssi->lock);
	/*
	 * We can have two UP events in a row due to a short low
	 * high transition. Therefore we need to ignore the sencond UP event.
	 */
	if ((ssi->main_state != ACTIVE) || (ssi->recv_state == RECV_READY)) {
		spin_unlock_bh(&ssi->lock);
		return;
	}
	ssip_set_rxstate(ssi, RECV_READY);
	spin_unlock_bh(&ssi->lock);

	msg = ssip_claim_cmd(ssi);
	ssip_set_cmd(msg, SSIP_READY_CMD);
	msg->complete = ssip_release_cmd;
	dev_dbg(&cl->device, "Send READY\n");
	hsi_async_write(cl, msg);
}