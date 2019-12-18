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
struct virtnet_info {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_NET_CTRL_ANNOUNCE ; 
 int /*<<< orphan*/  VIRTIO_NET_CTRL_ANNOUNCE_ACK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  virtnet_send_command (struct virtnet_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtnet_ack_link_announce(struct virtnet_info *vi)
{
	rtnl_lock();
	if (!virtnet_send_command(vi, VIRTIO_NET_CTRL_ANNOUNCE,
				  VIRTIO_NET_CTRL_ANNOUNCE_ACK, NULL))
		dev_warn(&vi->dev->dev, "Failed to ack link announce.\n");
	rtnl_unlock();
}