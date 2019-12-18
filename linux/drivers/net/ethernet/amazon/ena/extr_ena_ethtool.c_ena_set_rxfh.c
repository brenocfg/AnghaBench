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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ena_com_dev {int dummy; } ;
struct ena_adapter {struct ena_com_dev* ena_dev; } ;
typedef  enum ena_admin_hash_functions { ____Placeholder_ena_admin_hash_functions } ena_admin_hash_functions ;

/* Variables and functions */
 int ENA_ADMIN_CRC32 ; 
 int ENA_ADMIN_TOEPLITZ ; 
 int /*<<< orphan*/  ENA_HASH_KEY_SIZE ; 
 int /*<<< orphan*/  ENA_IO_RXQ_IDX (int /*<<< orphan*/  const) ; 
 int ENA_RX_RSS_TABLE_SIZE ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  ETH_RSS_HASH_TOP 129 
#define  ETH_RSS_HASH_XOR 128 
 int /*<<< orphan*/  drv ; 
 int ena_com_fill_hash_function (struct ena_com_dev*,int,int const*,int /*<<< orphan*/ ,int) ; 
 int ena_com_indirect_table_fill_entry (struct ena_com_dev*,int,int /*<<< orphan*/ ) ; 
 int ena_com_indirect_table_set (struct ena_com_dev*) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ena_set_rxfh(struct net_device *netdev, const u32 *indir,
			const u8 *key, const u8 hfunc)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	enum ena_admin_hash_functions func;
	int rc, i;

	if (indir) {
		for (i = 0; i < ENA_RX_RSS_TABLE_SIZE; i++) {
			rc = ena_com_indirect_table_fill_entry(ena_dev,
							       i,
							       ENA_IO_RXQ_IDX(indir[i]));
			if (unlikely(rc)) {
				netif_err(adapter, drv, netdev,
					  "Cannot fill indirect table (index is too large)\n");
				return rc;
			}
		}

		rc = ena_com_indirect_table_set(ena_dev);
		if (rc) {
			netif_err(adapter, drv, netdev,
				  "Cannot set indirect table\n");
			return rc == -EPERM ? -EOPNOTSUPP : rc;
		}
	}

	switch (hfunc) {
	case ETH_RSS_HASH_TOP:
		func = ENA_ADMIN_TOEPLITZ;
		break;
	case ETH_RSS_HASH_XOR:
		func = ENA_ADMIN_CRC32;
		break;
	default:
		netif_err(adapter, drv, netdev, "Unsupported hfunc %d\n",
			  hfunc);
		return -EOPNOTSUPP;
	}

	if (key) {
		rc = ena_com_fill_hash_function(ena_dev, func, key,
						ENA_HASH_KEY_SIZE,
						0xFFFFFFFF);
		if (unlikely(rc)) {
			netif_err(adapter, drv, netdev, "Cannot fill key\n");
			return rc == -EPERM ? -EOPNOTSUPP : rc;
		}
	}

	return 0;
}