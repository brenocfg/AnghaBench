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
typedef  scalar_t__ u32 ;
struct ssi_protocol {int main_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_wd; int /*<<< orphan*/  flags; } ;
struct hsi_msg {int /*<<< orphan*/  complete; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
#define  ACTIVE 130 
#define  HANDSHAKE 129 
#define  INIT 128 
 int /*<<< orphan*/  SSIP_BOOTINFO_RESP_CMD (int /*<<< orphan*/ ) ; 
 scalar_t__ SSIP_CMT_LOADER_SYNC ; 
 int /*<<< orphan*/  SSIP_DATA_VERSION (scalar_t__) ; 
 int /*<<< orphan*/  SSIP_LOCAL_VERID ; 
 int /*<<< orphan*/  SSIP_WAKETEST_FLAG ; 
 int /*<<< orphan*/  SSIP_WDTOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hsi_async_write (struct hsi_client*,struct hsi_msg*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssi_waketest (struct hsi_client*,int) ; 
 struct hsi_msg* ssip_claim_cmd (struct ssi_protocol*) ; 
 int /*<<< orphan*/  ssip_error (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_release_cmd ; 
 int /*<<< orphan*/  ssip_set_cmd (struct hsi_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ssip_rx_bootinforeq(struct hsi_client *cl, u32 cmd)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	struct hsi_msg *msg;

	/* Workaroud: Ignore CMT Loader message leftover */
	if (cmd == SSIP_CMT_LOADER_SYNC)
		return;

	switch (ssi->main_state) {
	case ACTIVE:
		dev_err(&cl->device, "Boot info req on active state\n");
		ssip_error(cl);
		/* Fall through */
	case INIT:
	case HANDSHAKE:
		spin_lock_bh(&ssi->lock);
		ssi->main_state = HANDSHAKE;
		spin_unlock_bh(&ssi->lock);

		if (!test_and_set_bit(SSIP_WAKETEST_FLAG, &ssi->flags))
			ssi_waketest(cl, 1); /* FIXME: To be removed */

		spin_lock_bh(&ssi->lock);
		/* Start boot handshake watchdog */
		mod_timer(&ssi->tx_wd, jiffies + msecs_to_jiffies(SSIP_WDTOUT));
		spin_unlock_bh(&ssi->lock);
		dev_dbg(&cl->device, "Send BOOTINFO_RESP\n");
		if (SSIP_DATA_VERSION(cmd) != SSIP_LOCAL_VERID)
			dev_warn(&cl->device, "boot info req verid mismatch\n");
		msg = ssip_claim_cmd(ssi);
		ssip_set_cmd(msg, SSIP_BOOTINFO_RESP_CMD(SSIP_LOCAL_VERID));
		msg->complete = ssip_release_cmd;
		hsi_async_write(cl, msg);
		break;
	default:
		dev_dbg(&cl->device, "Wrong state M(%d)\n", ssi->main_state);
		break;
	}
}