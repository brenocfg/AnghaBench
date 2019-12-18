#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vhci_unlink {int /*<<< orphan*/  unlink_seqnum; int /*<<< orphan*/  seqnum; } ;
struct TYPE_8__ {int /*<<< orphan*/  tcp_socket; } ;
struct vhci_device {TYPE_4__ ud; int /*<<< orphan*/  devid; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqnum; } ;
struct TYPE_7__ {TYPE_2__ cmd_unlink; } ;
struct TYPE_5__ {scalar_t__ ep; int /*<<< orphan*/  devid; int /*<<< orphan*/  seqnum; int /*<<< orphan*/  command; } ;
struct usbip_header {int iov_len; struct usbip_header* iov_base; TYPE_3__ u; TYPE_1__ base; } ;
struct msghdr {int iov_len; struct msghdr* iov_base; TYPE_3__ u; TYPE_1__ base; } ;
struct kvec {int iov_len; struct kvec* iov_base; TYPE_3__ u; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  pdu_header ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  iov ;

/* Variables and functions */
 int /*<<< orphan*/  USBIP_CMD_UNLINK ; 
 int /*<<< orphan*/  VDEV_EVENT_ERROR_TCP ; 
 struct vhci_unlink* dequeue_from_unlink_tx (struct vhci_device*) ; 
 int kernel_sendmsg (int /*<<< orphan*/ ,struct usbip_header*,struct usbip_header*,int,size_t) ; 
 int /*<<< orphan*/  memset (struct usbip_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,size_t) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_tx (char*,...) ; 
 int /*<<< orphan*/  usbip_event_add (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_header_correct_endian (struct usbip_header*,int) ; 

__attribute__((used)) static int vhci_send_cmd_unlink(struct vhci_device *vdev)
{
	struct vhci_unlink *unlink = NULL;

	struct msghdr msg;
	struct kvec iov;
	size_t txsize;
	size_t total_size = 0;

	while ((unlink = dequeue_from_unlink_tx(vdev)) != NULL) {
		int ret;
		struct usbip_header pdu_header;

		memset(&pdu_header, 0, sizeof(pdu_header));
		memset(&msg, 0, sizeof(msg));
		memset(&iov, 0, sizeof(iov));

		usbip_dbg_vhci_tx("setup cmd unlink, %lu\n", unlink->seqnum);

		/* 1. setup usbip_header */
		pdu_header.base.command = USBIP_CMD_UNLINK;
		pdu_header.base.seqnum  = unlink->seqnum;
		pdu_header.base.devid	= vdev->devid;
		pdu_header.base.ep	= 0;
		pdu_header.u.cmd_unlink.seqnum = unlink->unlink_seqnum;

		usbip_header_correct_endian(&pdu_header, 1);

		iov.iov_base = &pdu_header;
		iov.iov_len  = sizeof(pdu_header);
		txsize = sizeof(pdu_header);

		ret = kernel_sendmsg(vdev->ud.tcp_socket, &msg, &iov, 1, txsize);
		if (ret != txsize) {
			pr_err("sendmsg failed!, ret=%d for %zd\n", ret,
			       txsize);
			usbip_event_add(&vdev->ud, VDEV_EVENT_ERROR_TCP);
			return -1;
		}

		usbip_dbg_vhci_tx("send txdata\n");

		total_size += txsize;
	}

	return total_size;
}