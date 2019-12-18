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
struct vnet_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ stype; int /*<<< orphan*/  sid; int /*<<< orphan*/  stype_env; int /*<<< orphan*/  type; } ;
struct vio_net_mcast_info {TYPE_1__ tag; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ VIO_SUBTYPE_ACK ; 
 struct net_device* VNET_PORT_TO_NET_DEVICE (struct vnet_port*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_mcast(struct vnet_port *port, void *msgbuf)
{
	struct vio_net_mcast_info *pkt = msgbuf;
	struct net_device *dev = VNET_PORT_TO_NET_DEVICE(port);

	if (pkt->tag.stype != VIO_SUBTYPE_ACK)
		pr_err("%s: Got unexpected MCAST reply [%02x:%02x:%04x:%08x]\n",
		       dev->name,
		       pkt->tag.type,
		       pkt->tag.stype,
		       pkt->tag.stype_env,
		       pkt->tag.sid);

	return 0;
}