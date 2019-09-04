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
struct pci_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ixgbe_pci_sriov_enable(struct pci_dev *dev, int num_vfs)
{
#ifdef CONFIG_PCI_IOV
	struct ixgbe_adapter *adapter = pci_get_drvdata(dev);
	int pre_existing_vfs = pci_num_vf(dev);
	int err = 0, num_rx_pools, i, limit;
	u8 num_tc;

	if (pre_existing_vfs && pre_existing_vfs != num_vfs)
		err = ixgbe_disable_sriov(adapter);
	else if (pre_existing_vfs && pre_existing_vfs == num_vfs)
		return num_vfs;

	if (err)
		return err;

	/* While the SR-IOV capability structure reports total VFs to be 64,
	 * we limit the actual number allocated as below based on two factors.
	 *    Num_TCs	MAX_VFs
	 *	1	  63
	 *	<=4	  31
	 *	>4	  15
	 * First, we reserve some transmit/receive resources for the PF.
	 * Second, VMDQ also uses the same pools that SR-IOV does. We need to
	 * account for this, so that we don't accidentally allocate more VFs
	 * than we have available pools. The PCI bus driver already checks for
	 * other values out of range.
	 */
	num_tc = adapter->hw_tcs;
	num_rx_pools = bitmap_weight(adapter->fwd_bitmask,
				     adapter->num_rx_pools);
	limit = (num_tc > 4) ? IXGBE_MAX_VFS_8TC :
		(num_tc > 1) ? IXGBE_MAX_VFS_4TC : IXGBE_MAX_VFS_1TC;

	if (num_vfs > (limit - num_rx_pools)) {
		e_dev_err("Currently configured with %d TCs, and %d offloaded macvlans. Creating more than %d VFs is not allowed\n",
			  num_tc, num_rx_pools - 1, limit - num_rx_pools);
		return -EPERM;
	}

	err = __ixgbe_enable_sriov(adapter, num_vfs);
	if (err)
		return  err;

	for (i = 0; i < num_vfs; i++)
		ixgbe_vf_configuration(dev, (i | 0x10000000));

	/* reset before enabling SRIOV to avoid mailbox issues */
	ixgbe_sriov_reinit(adapter);

	err = pci_enable_sriov(dev, num_vfs);
	if (err) {
		e_dev_warn("Failed to enable PCI sriov: %d\n", err);
		return err;
	}
	ixgbe_get_vfs(adapter);

	return num_vfs;
#else
	return 0;
#endif
}