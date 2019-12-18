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
struct msgbuf_common_hdr {int msgtype; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_msgbuf {struct brcmf_pub* drvr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGBUF ; 
#define  MSGBUF_TYPE_FLOW_RING_CREATE_CMPLT 136 
#define  MSGBUF_TYPE_FLOW_RING_DELETE_CMPLT 135 
#define  MSGBUF_TYPE_GEN_STATUS 134 
#define  MSGBUF_TYPE_IOCTLPTR_REQ_ACK 133 
#define  MSGBUF_TYPE_IOCTL_CMPLT 132 
#define  MSGBUF_TYPE_RING_STATUS 131 
#define  MSGBUF_TYPE_RX_CMPLT 130 
#define  MSGBUF_TYPE_TX_STATUS 129 
#define  MSGBUF_TYPE_WL_EVENT 128 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_process_event (struct brcmf_msgbuf*,void*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_process_flow_ring_create_response (struct brcmf_msgbuf*,void*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_process_flow_ring_delete_response (struct brcmf_msgbuf*,void*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_process_gen_status (struct brcmf_msgbuf*,void*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_process_ioctl_complete (struct brcmf_msgbuf*,void*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_process_ring_status (struct brcmf_msgbuf*,void*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_process_rx_complete (struct brcmf_msgbuf*,void*) ; 
 int /*<<< orphan*/  brcmf_msgbuf_process_txstatus (struct brcmf_msgbuf*,void*) ; 

__attribute__((used)) static void brcmf_msgbuf_process_msgtype(struct brcmf_msgbuf *msgbuf, void *buf)
{
	struct brcmf_pub *drvr = msgbuf->drvr;
	struct msgbuf_common_hdr *msg;

	msg = (struct msgbuf_common_hdr *)buf;
	switch (msg->msgtype) {
	case MSGBUF_TYPE_GEN_STATUS:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_GEN_STATUS\n");
		brcmf_msgbuf_process_gen_status(msgbuf, buf);
		break;
	case MSGBUF_TYPE_RING_STATUS:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_RING_STATUS\n");
		brcmf_msgbuf_process_ring_status(msgbuf, buf);
		break;
	case MSGBUF_TYPE_FLOW_RING_CREATE_CMPLT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_FLOW_RING_CREATE_CMPLT\n");
		brcmf_msgbuf_process_flow_ring_create_response(msgbuf, buf);
		break;
	case MSGBUF_TYPE_FLOW_RING_DELETE_CMPLT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_FLOW_RING_DELETE_CMPLT\n");
		brcmf_msgbuf_process_flow_ring_delete_response(msgbuf, buf);
		break;
	case MSGBUF_TYPE_IOCTLPTR_REQ_ACK:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_IOCTLPTR_REQ_ACK\n");
		break;
	case MSGBUF_TYPE_IOCTL_CMPLT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_IOCTL_CMPLT\n");
		brcmf_msgbuf_process_ioctl_complete(msgbuf, buf);
		break;
	case MSGBUF_TYPE_WL_EVENT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_WL_EVENT\n");
		brcmf_msgbuf_process_event(msgbuf, buf);
		break;
	case MSGBUF_TYPE_TX_STATUS:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_TX_STATUS\n");
		brcmf_msgbuf_process_txstatus(msgbuf, buf);
		break;
	case MSGBUF_TYPE_RX_CMPLT:
		brcmf_dbg(MSGBUF, "MSGBUF_TYPE_RX_CMPLT\n");
		brcmf_msgbuf_process_rx_complete(msgbuf, buf);
		break;
	default:
		bphy_err(drvr, "Unsupported msgtype %d\n", msg->msgtype);
		break;
	}
}