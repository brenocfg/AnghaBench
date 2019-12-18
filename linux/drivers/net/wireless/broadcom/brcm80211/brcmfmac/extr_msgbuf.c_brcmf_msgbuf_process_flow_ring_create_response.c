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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  flow_ring_id; } ;
struct msgbuf_flowring_create_resp {TYPE_1__ compl_hdr; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_msgbuf {int /*<<< orphan*/  flow; struct brcmf_pub* drvr; } ;

/* Variables and functions */
 scalar_t__ BRCMF_H2D_MSGRING_FLOWRING_IDSTART ; 
 int /*<<< orphan*/  MSGBUF ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_flowring_open (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_msgbuf_remove_flowring (struct brcmf_msgbuf*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_msgbuf_schedule_txdata (struct brcmf_msgbuf*,scalar_t__,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcmf_msgbuf_process_flow_ring_create_response(struct brcmf_msgbuf *msgbuf,
					       void *buf)
{
	struct brcmf_pub *drvr = msgbuf->drvr;
	struct msgbuf_flowring_create_resp *flowring_create_resp;
	u16 status;
	u16 flowid;

	flowring_create_resp = (struct msgbuf_flowring_create_resp *)buf;

	flowid = le16_to_cpu(flowring_create_resp->compl_hdr.flow_ring_id);
	flowid -= BRCMF_H2D_MSGRING_FLOWRING_IDSTART;
	status =  le16_to_cpu(flowring_create_resp->compl_hdr.status);

	if (status) {
		bphy_err(drvr, "Flowring creation failed, code %d\n", status);
		brcmf_msgbuf_remove_flowring(msgbuf, flowid);
		return;
	}
	brcmf_dbg(MSGBUF, "Flowring %d Create response status %d\n", flowid,
		  status);

	brcmf_flowring_open(msgbuf->flow, flowid);

	brcmf_msgbuf_schedule_txdata(msgbuf, flowid, true);
}