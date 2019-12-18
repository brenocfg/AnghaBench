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
typedef  int /*<<< orphan*/  u32 ;
struct hsi_msg {scalar_t__ status; struct hsi_client* cl; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ HSI_STATUS_ERROR ; 
#define  SSIP_BOOTINFO_REQ 133 
#define  SSIP_BOOTINFO_RESP 132 
 unsigned int SSIP_COMMAND (int /*<<< orphan*/ ) ; 
#define  SSIP_READY 131 
#define  SSIP_START_TRANS 130 
#define  SSIP_SW_BREAK 129 
#define  SSIP_WAKETEST_RESULT 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_async_read (struct hsi_client*,struct hsi_msg*) ; 
 int /*<<< orphan*/  ssip_error (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_get_cmd (struct hsi_msg*) ; 
 int /*<<< orphan*/  ssip_release_cmd (struct hsi_msg*) ; 
 int /*<<< orphan*/  ssip_rx_bootinforeq (struct hsi_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_rx_bootinforesp (struct hsi_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_rx_ready (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_rx_strans (struct hsi_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssip_rx_waketest (struct hsi_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssip_rxcmd_complete(struct hsi_msg *msg)
{
	struct hsi_client *cl = msg->cl;
	u32 cmd = ssip_get_cmd(msg);
	unsigned int cmdid = SSIP_COMMAND(cmd);

	if (msg->status == HSI_STATUS_ERROR) {
		dev_err(&cl->device, "RX error detected\n");
		ssip_release_cmd(msg);
		ssip_error(cl);
		return;
	}
	hsi_async_read(cl, msg);
	dev_dbg(&cl->device, "RX cmd: 0x%08x\n", cmd);
	switch (cmdid) {
	case SSIP_SW_BREAK:
		/* Ignored */
		break;
	case SSIP_BOOTINFO_REQ:
		ssip_rx_bootinforeq(cl, cmd);
		break;
	case SSIP_BOOTINFO_RESP:
		ssip_rx_bootinforesp(cl, cmd);
		break;
	case SSIP_WAKETEST_RESULT:
		ssip_rx_waketest(cl, cmd);
		break;
	case SSIP_START_TRANS:
		ssip_rx_strans(cl, cmd);
		break;
	case SSIP_READY:
		ssip_rx_ready(cl);
		break;
	default:
		dev_warn(&cl->device, "command 0x%08x not supported\n", cmd);
		break;
	}
}