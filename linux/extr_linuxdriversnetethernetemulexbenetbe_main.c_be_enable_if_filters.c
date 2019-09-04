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
struct be_adapter {int* pmac_id; scalar_t__ vlans_added; TYPE_1__* netdev; int /*<<< orphan*/  dev_mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_IF_FILT_FLAGS_BASIC ; 
 int /*<<< orphan*/  ON ; 
 int /*<<< orphan*/  __be_set_rx_mode (struct be_adapter*) ; 
 int be_cmd_rx_filter (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_dev_mac_add (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_dev_mac_del (struct be_adapter*,int) ; 
 int /*<<< orphan*/  be_vid_config (struct be_adapter*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_enable_if_filters(struct be_adapter *adapter)
{
	int status;

	status = be_cmd_rx_filter(adapter, BE_IF_FILT_FLAGS_BASIC, ON);
	if (status)
		return status;

	/* Normally this condition usually true as the ->dev_mac is zeroed.
	 * But on BE3 VFs the initial MAC is pre-programmed by PF and
	 * subsequent be_dev_mac_add() can fail (after fresh boot)
	 */
	if (!ether_addr_equal(adapter->dev_mac, adapter->netdev->dev_addr)) {
		int old_pmac_id = -1;

		/* Remember old programmed MAC if any - can happen on BE3 VF */
		if (!is_zero_ether_addr(adapter->dev_mac))
			old_pmac_id = adapter->pmac_id[0];

		status = be_dev_mac_add(adapter, adapter->netdev->dev_addr);
		if (status)
			return status;

		/* Delete the old programmed MAC as we successfully programmed
		 * a new MAC
		 */
		if (old_pmac_id >= 0 && old_pmac_id != adapter->pmac_id[0])
			be_dev_mac_del(adapter, old_pmac_id);

		ether_addr_copy(adapter->dev_mac, adapter->netdev->dev_addr);
	}

	if (adapter->vlans_added)
		be_vid_config(adapter);

	__be_set_rx_mode(adapter);

	return 0;
}