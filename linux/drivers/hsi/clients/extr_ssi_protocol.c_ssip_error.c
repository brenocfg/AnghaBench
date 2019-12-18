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
struct hsi_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hsi_async_read (struct hsi_client*,struct hsi_msg*) ; 
 struct ssi_protocol* hsi_client_drvdata (struct hsi_client*) ; 
 struct hsi_msg* ssip_claim_cmd (struct ssi_protocol*) ; 
 int /*<<< orphan*/  ssip_dump_state (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_reset (struct hsi_client*) ; 
 int /*<<< orphan*/  ssip_rxcmd_complete ; 

__attribute__((used)) static void ssip_error(struct hsi_client *cl)
{
	struct ssi_protocol *ssi = hsi_client_drvdata(cl);
	struct hsi_msg *msg;

	ssip_dump_state(cl);
	ssip_reset(cl);
	msg = ssip_claim_cmd(ssi);
	msg->complete = ssip_rxcmd_complete;
	hsi_async_read(cl, msg);
}