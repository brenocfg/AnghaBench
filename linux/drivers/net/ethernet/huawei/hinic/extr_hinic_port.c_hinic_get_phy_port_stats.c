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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_port_stats_info {int stats_size; int /*<<< orphan*/  stats_version; int /*<<< orphan*/  member_0; } ;
struct hinic_port_stats {int /*<<< orphan*/  stats; scalar_t__ status; } ;
struct hinic_phy_port_stats {int dummy; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  stats_info ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HINIC_PORT_CMD_GET_PORT_STATISTICS ; 
 int /*<<< orphan*/  HINIC_PORT_STATS_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int) ; 
 int hinic_port_msg_cmd (struct hinic_hwdev*,int /*<<< orphan*/ ,struct hinic_port_stats_info*,int,struct hinic_port_stats*,int*) ; 
 int /*<<< orphan*/  kfree (struct hinic_port_stats*) ; 
 struct hinic_port_stats* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct hinic_phy_port_stats*,int /*<<< orphan*/ *,int) ; 

int hinic_get_phy_port_stats(struct hinic_dev *nic_dev,
			     struct hinic_phy_port_stats *stats)
{
	struct hinic_port_stats_info stats_info = { 0 };
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct hinic_port_stats *port_stats;
	u16 out_size = sizeof(*port_stats);
	struct pci_dev *pdev = hwif->pdev;
	int err;

	port_stats = kzalloc(sizeof(*port_stats), GFP_KERNEL);
	if (!port_stats)
		return -ENOMEM;

	stats_info.stats_version = HINIC_PORT_STATS_VERSION;
	stats_info.stats_size = sizeof(*port_stats);

	err = hinic_port_msg_cmd(hwdev, HINIC_PORT_CMD_GET_PORT_STATISTICS,
				 &stats_info, sizeof(stats_info),
				 port_stats, &out_size);
	if (err || !out_size || port_stats->status) {
		dev_err(&pdev->dev,
			"Failed to get port statistics, err: %d, status: 0x%x, out size: 0x%x\n",
			err, port_stats->status, out_size);
		err = -EINVAL;
		goto out;
	}

	memcpy(stats, &port_stats->stats, sizeof(*stats));

out:
	kfree(port_stats);

	return err;
}