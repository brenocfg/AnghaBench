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
struct netvsc_device_info {unsigned int num_chn; } ;
struct netvsc_device {scalar_t__ nvsp_version; unsigned int max_chn; unsigned int num_chn; scalar_t__ destroy; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {unsigned int combined_count; scalar_t__ other_count; scalar_t__ tx_count; scalar_t__ rx_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ NVSP_PROTOCOL_VERSION_5 ; 
 int /*<<< orphan*/  kfree (struct netvsc_device_info*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int netvsc_attach (struct net_device*,struct netvsc_device_info*) ; 
 int netvsc_detach (struct net_device*,struct netvsc_device*) ; 
 struct netvsc_device_info* netvsc_devinfo_get (struct netvsc_device*) ; 
 struct netvsc_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netvsc_set_channels(struct net_device *net,
			       struct ethtool_channels *channels)
{
	struct net_device_context *net_device_ctx = netdev_priv(net);
	struct netvsc_device *nvdev = rtnl_dereference(net_device_ctx->nvdev);
	unsigned int orig, count = channels->combined_count;
	struct netvsc_device_info *device_info;
	int ret;

	/* We do not support separate count for rx, tx, or other */
	if (count == 0 ||
	    channels->rx_count || channels->tx_count || channels->other_count)
		return -EINVAL;

	if (!nvdev || nvdev->destroy)
		return -ENODEV;

	if (nvdev->nvsp_version < NVSP_PROTOCOL_VERSION_5)
		return -EINVAL;

	if (count > nvdev->max_chn)
		return -EINVAL;

	orig = nvdev->num_chn;

	device_info = netvsc_devinfo_get(nvdev);

	if (!device_info)
		return -ENOMEM;

	device_info->num_chn = count;

	ret = netvsc_detach(net, nvdev);
	if (ret)
		goto out;

	ret = netvsc_attach(net, device_info);
	if (ret) {
		device_info->num_chn = orig;
		if (netvsc_attach(net, device_info))
			netdev_err(net, "restoring channel setting failed\n");
	}

out:
	kfree(device_info);
	return ret;
}