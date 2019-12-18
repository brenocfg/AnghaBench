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
typedef  scalar_t__ uint32_t ;
struct ishtp_msg_hdr {scalar_t__ length; int /*<<< orphan*/  host_addr; int /*<<< orphan*/  fw_addr; } ;
struct ishtp_device {scalar_t__ mtu; int /*<<< orphan*/  devc; scalar_t__ ishtp_msg_hdr; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sync_fw_clock ) (struct ishtp_device*) ;scalar_t__ (* ishtp_read_hdr ) (struct ishtp_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  recv_fixed_cl_msg (struct ishtp_device*,struct ishtp_msg_hdr*) ; 
 int /*<<< orphan*/  recv_hbm (struct ishtp_device*,struct ishtp_msg_hdr*) ; 
 int /*<<< orphan*/  recv_ishtp_cl_msg (struct ishtp_device*,struct ishtp_msg_hdr*) ; 
 scalar_t__ stub1 (struct ishtp_device*) ; 
 int /*<<< orphan*/  stub2 (struct ishtp_device*) ; 

void ishtp_recv(struct ishtp_device *dev)
{
	uint32_t	msg_hdr;
	struct ishtp_msg_hdr	*ishtp_hdr;

	/* Read ISHTP header dword */
	msg_hdr = dev->ops->ishtp_read_hdr(dev);
	if (!msg_hdr)
		return;

	dev->ops->sync_fw_clock(dev);

	ishtp_hdr = (struct ishtp_msg_hdr *)&msg_hdr;
	dev->ishtp_msg_hdr = msg_hdr;

	/* Sanity check: ISHTP frag. length in header */
	if (ishtp_hdr->length > dev->mtu) {
		dev_err(dev->devc,
			"ISHTP hdr - bad length: %u; dropped [%08X]\n",
			(unsigned int)ishtp_hdr->length, msg_hdr);
		return;
	}

	/* ISHTP bus message */
	if (!ishtp_hdr->host_addr && !ishtp_hdr->fw_addr)
		recv_hbm(dev, ishtp_hdr);
	/* ISHTP fixed-client message */
	else if (!ishtp_hdr->host_addr)
		recv_fixed_cl_msg(dev, ishtp_hdr);
	else
		/* ISHTP client message */
		recv_ishtp_cl_msg(dev, ishtp_hdr);
}