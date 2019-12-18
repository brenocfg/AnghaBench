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
typedef  char u8 ;
typedef  char u64 ;
struct net_device {int dummy; } ;
struct ena_adapter {TYPE_1__* pdev; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  ETH_SS_STATS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 char* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ena_get_ethtool_stats (struct net_device*,int /*<<< orphan*/ *,char*) ; 
 int ena_get_sset_count (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_get_strings (struct net_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int snprintf (char*,int,char*,char*,char) ; 

__attribute__((used)) static void ena_dump_stats_ex(struct ena_adapter *adapter, u8 *buf)
{
	struct net_device *netdev = adapter->netdev;
	u8 *strings_buf;
	u64 *data_buf;
	int strings_num;
	int i, rc;

	strings_num = ena_get_sset_count(netdev, ETH_SS_STATS);
	if (strings_num <= 0) {
		netif_err(adapter, drv, netdev, "Can't get stats num\n");
		return;
	}

	strings_buf = devm_kcalloc(&adapter->pdev->dev,
				   ETH_GSTRING_LEN, strings_num,
				   GFP_ATOMIC);
	if (!strings_buf) {
		netif_err(adapter, drv, netdev,
			  "failed to alloc strings_buf\n");
		return;
	}

	data_buf = devm_kcalloc(&adapter->pdev->dev,
				strings_num, sizeof(u64),
				GFP_ATOMIC);
	if (!data_buf) {
		netif_err(adapter, drv, netdev,
			  "failed to allocate data buf\n");
		devm_kfree(&adapter->pdev->dev, strings_buf);
		return;
	}

	ena_get_strings(netdev, ETH_SS_STATS, strings_buf);
	ena_get_ethtool_stats(netdev, NULL, data_buf);

	/* If there is a buffer, dump stats, otherwise print them to dmesg */
	if (buf)
		for (i = 0; i < strings_num; i++) {
			rc = snprintf(buf, ETH_GSTRING_LEN + sizeof(u64),
				      "%s %llu\n",
				      strings_buf + i * ETH_GSTRING_LEN,
				      data_buf[i]);
			buf += rc;
		}
	else
		for (i = 0; i < strings_num; i++)
			netif_err(adapter, drv, netdev, "%s: %llu\n",
				  strings_buf + i * ETH_GSTRING_LEN,
				  data_buf[i]);

	devm_kfree(&adapter->pdev->dev, strings_buf);
	devm_kfree(&adapter->pdev->dev, data_buf);
}