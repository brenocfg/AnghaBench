#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct be_adapter {int num_vfs; TYPE_2__* vf_cfg; TYPE_1__* pdev; } ;
struct TYPE_4__ {int tx_rate; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int EPERM ; 
 int be_cmd_config_qos (struct be_adapter*,int,int,int) ; 
 int be_cmd_link_status_query (struct be_adapter*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int be_cmd_status (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ skyhawk_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  sriov_enabled (struct be_adapter*) ; 

__attribute__((used)) static int be_set_vf_tx_rate(struct net_device *netdev, int vf,
			     int min_tx_rate, int max_tx_rate)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	struct device *dev = &adapter->pdev->dev;
	int percent_rate, status = 0;
	u16 link_speed = 0;
	u8 link_status;

	if (!sriov_enabled(adapter))
		return -EPERM;

	if (vf >= adapter->num_vfs)
		return -EINVAL;

	if (min_tx_rate)
		return -EINVAL;

	if (!max_tx_rate)
		goto config_qos;

	status = be_cmd_link_status_query(adapter, &link_speed,
					  &link_status, 0);
	if (status)
		goto err;

	if (!link_status) {
		dev_err(dev, "TX-rate setting not allowed when link is down\n");
		status = -ENETDOWN;
		goto err;
	}

	if (max_tx_rate < 100 || max_tx_rate > link_speed) {
		dev_err(dev, "TX-rate must be between 100 and %d Mbps\n",
			link_speed);
		status = -EINVAL;
		goto err;
	}

	/* On Skyhawk the QOS setting must be done only as a % value */
	percent_rate = link_speed / 100;
	if (skyhawk_chip(adapter) && (max_tx_rate % percent_rate)) {
		dev_err(dev, "TX-rate must be a multiple of %d Mbps\n",
			percent_rate);
		status = -EINVAL;
		goto err;
	}

config_qos:
	status = be_cmd_config_qos(adapter, max_tx_rate, link_speed, vf + 1);
	if (status)
		goto err;

	adapter->vf_cfg[vf].tx_rate = max_tx_rate;
	return 0;

err:
	dev_err(dev, "TX-rate setting of %dMbps on VF%d failed\n",
		max_tx_rate, vf);
	return be_cmd_status(status);
}