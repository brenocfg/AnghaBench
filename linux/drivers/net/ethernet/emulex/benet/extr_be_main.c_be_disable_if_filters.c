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
struct be_adapter {int /*<<< orphan*/  if_flags; int /*<<< orphan*/  dev_mac; int /*<<< orphan*/ * pmac_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_IF_ALL_FILT_FLAGS ; 
 int /*<<< orphan*/  BE_PRIV_FILTMGMT ; 
 int /*<<< orphan*/  BEx_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  be_clear_mc_list (struct be_adapter*) ; 
 int /*<<< orphan*/  be_clear_uc_list (struct be_adapter*) ; 
 int /*<<< orphan*/  be_cmd_rx_filter (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_dev_mac_del (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_virtfn (struct be_adapter*) ; 
 scalar_t__ check_privilege (struct be_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 

__attribute__((used)) static void be_disable_if_filters(struct be_adapter *adapter)
{
	/* Don't delete MAC on BE3 VFs without FILTMGMT privilege  */
	if (!BEx_chip(adapter) || !be_virtfn(adapter) ||
	    check_privilege(adapter, BE_PRIV_FILTMGMT)) {
		be_dev_mac_del(adapter, adapter->pmac_id[0]);
		eth_zero_addr(adapter->dev_mac);
	}

	be_clear_uc_list(adapter);
	be_clear_mc_list(adapter);

	/* The IFACE flags are enabled in the open path and cleared
	 * in the close path. When a VF gets detached from the host and
	 * assigned to a VM the following happens:
	 *	- VF's IFACE flags get cleared in the detach path
	 *	- IFACE create is issued by the VF in the attach path
	 * Due to a bug in the BE3/Skyhawk-R FW
	 * (Lancer FW doesn't have the bug), the IFACE capability flags
	 * specified along with the IFACE create cmd issued by a VF are not
	 * honoured by FW.  As a consequence, if a *new* driver
	 * (that enables/disables IFACE flags in open/close)
	 * is loaded in the host and an *old* driver is * used by a VM/VF,
	 * the IFACE gets created *without* the needed flags.
	 * To avoid this, disable RX-filter flags only for Lancer.
	 */
	if (lancer_chip(adapter)) {
		be_cmd_rx_filter(adapter, BE_IF_ALL_FILT_FLAGS, OFF);
		adapter->if_flags &= ~BE_IF_ALL_FILT_FLAGS;
	}
}