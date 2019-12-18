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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ena_adapter {int /*<<< orphan*/  ena_dev; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  ETH_SS_STATS ; 
 int /*<<< orphan*/  drv ; 
 int ena_com_allocate_debug_area (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ena_com_delete_debug_area (int /*<<< orphan*/ ) ; 
 int ena_com_set_host_attributes (int /*<<< orphan*/ ) ; 
 int ena_get_sset_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_warn (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void ena_config_debug_area(struct ena_adapter *adapter)
{
	u32 debug_area_size;
	int rc, ss_count;

	ss_count = ena_get_sset_count(adapter->netdev, ETH_SS_STATS);
	if (ss_count <= 0) {
		netif_err(adapter, drv, adapter->netdev,
			  "SS count is negative\n");
		return;
	}

	/* allocate 32 bytes for each string and 64bit for the value */
	debug_area_size = ss_count * ETH_GSTRING_LEN + sizeof(u64) * ss_count;

	rc = ena_com_allocate_debug_area(adapter->ena_dev, debug_area_size);
	if (rc) {
		pr_err("Cannot allocate debug area\n");
		return;
	}

	rc = ena_com_set_host_attributes(adapter->ena_dev);
	if (rc) {
		if (rc == -EOPNOTSUPP)
			netif_warn(adapter, drv, adapter->netdev,
				   "Cannot set host attributes\n");
		else
			netif_err(adapter, drv, adapter->netdev,
				  "Cannot set host attributes\n");
		goto err;
	}

	return;
err:
	ena_com_delete_debug_area(adapter->ena_dev);
}