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
typedef  int /*<<< orphan*/  u16 ;
struct virtnet_info {TYPE_1__* ctrl; int /*<<< orphan*/  vdev; } ;
struct scatterlist {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_NET_CTRL_VLAN ; 
 int /*<<< orphan*/  VIRTIO_NET_CTRL_VLAN_ADD ; 
 int /*<<< orphan*/  cpu_to_virtio16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  virtnet_send_command (struct virtnet_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scatterlist*) ; 

__attribute__((used)) static int virtnet_vlan_rx_add_vid(struct net_device *dev,
				   __be16 proto, u16 vid)
{
	struct virtnet_info *vi = netdev_priv(dev);
	struct scatterlist sg;

	vi->ctrl->vid = cpu_to_virtio16(vi->vdev, vid);
	sg_init_one(&sg, &vi->ctrl->vid, sizeof(vi->ctrl->vid));

	if (!virtnet_send_command(vi, VIRTIO_NET_CTRL_VLAN,
				  VIRTIO_NET_CTRL_VLAN_ADD, &sg))
		dev_warn(&dev->dev, "Failed to add VLAN ID %d.\n", vid);
	return 0;
}