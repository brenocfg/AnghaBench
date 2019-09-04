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
struct ssi_protocol {int dummy; } ;
struct hsi_msg {int /*<<< orphan*/  complete; } ;
struct hsi_client {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSIP_BOOTINFO_REQ_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSIP_LOCAL_VERID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hsi_async_read (struct hsi_client*,struct hsi_msg*) ; 
 int /*<<< orphan*/  hsi_async_write (struct hsi_client*,struct hsi_msg*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 struct hsi_msg* ssip_claim_cmd (struct ssi_protocol*) ; 
 int /*<<< orphan*/  ssip_release_cmd ; 
 int /*<<< orphan*/  ssip_rxcmd_complete ; 
 int /*<<< orphan*/  ssip_set_cmd (struct hsi_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssip_send_bootinfo_req_cmd(struct hsi_client *cl)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	struct hsi_msg *msg;

	dev_dbg(&cl->device, "Issuing BOOT INFO REQ command\n");
	msg = ssip_claim_cmd(ssi);
	ssip_set_cmd(msg, SSIP_BOOTINFO_REQ_CMD(SSIP_LOCAL_VERID));
	msg->complete = ssip_release_cmd;
	hsi_async_write(cl, msg);
	dev_dbg(&cl->device, "Issuing RX command\n");
	msg = ssip_claim_cmd(ssi);
	msg->complete = ssip_rxcmd_complete;
	hsi_async_read(cl, msg);
}