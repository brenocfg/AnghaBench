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
struct virtnet_info {int /*<<< orphan*/  vdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  VIRTIO_NET_F_STANDBY ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int snprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  virtio_has_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtnet_get_phys_port_name(struct net_device *dev, char *buf,
				      size_t len)
{
	struct virtnet_info *vi = netdev_priv(dev);
	int ret;

	if (!virtio_has_feature(vi->vdev, VIRTIO_NET_F_STANDBY))
		return -EOPNOTSUPP;

	ret = snprintf(buf, len, "sby");
	if (ret >= len)
		return -EOPNOTSUPP;

	return 0;
}