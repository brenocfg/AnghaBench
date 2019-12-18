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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ena_adapter {int /*<<< orphan*/  ena_dev; } ;
typedef  enum ena_admin_hash_functions { ____Placeholder_ena_admin_hash_functions } ena_admin_hash_functions ;

/* Variables and functions */
#define  ENA_ADMIN_CRC32 129 
#define  ENA_ADMIN_TOEPLITZ 128 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_RSS_HASH_TOP ; 
 int /*<<< orphan*/  ETH_RSS_HASH_XOR ; 
 int /*<<< orphan*/  drv ; 
 int ena_com_get_hash_function (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int ena_com_indirect_table_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static int ena_get_rxfh(struct net_device *netdev, u32 *indir, u8 *key,
			u8 *hfunc)
{
	struct ena_adapter *adapter = netdev_priv(netdev);
	enum ena_admin_hash_functions ena_func;
	u8 func;
	int rc;

	rc = ena_com_indirect_table_get(adapter->ena_dev, indir);
	if (rc)
		return rc;

	rc = ena_com_get_hash_function(adapter->ena_dev, &ena_func, key);
	if (rc)
		return rc;

	switch (ena_func) {
	case ENA_ADMIN_TOEPLITZ:
		func = ETH_RSS_HASH_TOP;
		break;
	case ENA_ADMIN_CRC32:
		func = ETH_RSS_HASH_XOR;
		break;
	default:
		netif_err(adapter, drv, netdev,
			  "Command parameter is not supported\n");
		return -EOPNOTSUPP;
	}

	if (hfunc)
		*hfunc = func;

	return rc;
}