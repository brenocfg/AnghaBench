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
typedef  scalar_t__ u64 ;
struct iproc_pcie_ob_map {int nr_sizes; scalar_t__* window_sizes; } ;
struct iproc_pcie_ob {scalar_t__ axi_offset; int nr_windows; } ;
struct iproc_pcie {struct iproc_pcie_ob_map* ob_map; struct device* dev; struct iproc_pcie_ob ob; } ;
struct device {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 scalar_t__ ALIGN_DOWN (scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,scalar_t__) ; 
 scalar_t__ SZ_1M ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ iproc_pcie_ob_is_valid (struct iproc_pcie*,int) ; 
 int iproc_pcie_ob_write (struct iproc_pcie*,int,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int iproc_pcie_setup_ob(struct iproc_pcie *pcie, u64 axi_addr,
			       u64 pci_addr, resource_size_t size)
{
	struct iproc_pcie_ob *ob = &pcie->ob;
	struct device *dev = pcie->dev;
	int ret = -EINVAL, window_idx, size_idx;

	if (axi_addr < ob->axi_offset) {
		dev_err(dev, "axi address %pap less than offset %pap\n",
			&axi_addr, &ob->axi_offset);
		return -EINVAL;
	}

	/*
	 * Translate the AXI address to the internal address used by the iProc
	 * PCIe core before programming the OARR
	 */
	axi_addr -= ob->axi_offset;

	/* iterate through all OARR/OMAP mapping windows */
	for (window_idx = ob->nr_windows - 1; window_idx >= 0; window_idx--) {
		const struct iproc_pcie_ob_map *ob_map =
			&pcie->ob_map[window_idx];

		/*
		 * If current outbound window is already in use, move on to the
		 * next one.
		 */
		if (iproc_pcie_ob_is_valid(pcie, window_idx))
			continue;

		/*
		 * Iterate through all supported window sizes within the
		 * OARR/OMAP pair to find a match.  Go through the window sizes
		 * in a descending order.
		 */
		for (size_idx = ob_map->nr_sizes - 1; size_idx >= 0;
		     size_idx--) {
			resource_size_t window_size =
				ob_map->window_sizes[size_idx] * SZ_1M;

			/*
			 * Keep iterating until we reach the last window and
			 * with the minimal window size at index zero. In this
			 * case, we take a compromise by mapping it using the
			 * minimum window size that can be supported
			 */
			if (size < window_size) {
				if (size_idx > 0 || window_idx > 0)
					continue;

				/*
				 * For the corner case of reaching the minimal
				 * window size that can be supported on the
				 * last window
				 */
				axi_addr = ALIGN_DOWN(axi_addr, window_size);
				pci_addr = ALIGN_DOWN(pci_addr, window_size);
				size = window_size;
			}

			if (!IS_ALIGNED(axi_addr, window_size) ||
			    !IS_ALIGNED(pci_addr, window_size)) {
				dev_err(dev,
					"axi %pap or pci %pap not aligned\n",
					&axi_addr, &pci_addr);
				return -EINVAL;
			}

			/*
			 * Match found!  Program both OARR and OMAP and mark
			 * them as a valid entry.
			 */
			ret = iproc_pcie_ob_write(pcie, window_idx, size_idx,
						  axi_addr, pci_addr);
			if (ret)
				goto err_ob;

			size -= window_size;
			if (size == 0)
				return 0;

			/*
			 * If we are here, we are done with the current window,
			 * but not yet finished all mappings.  Need to move on
			 * to the next window.
			 */
			axi_addr += window_size;
			pci_addr += window_size;
			break;
		}
	}

err_ob:
	dev_err(dev, "unable to configure outbound mapping\n");
	dev_err(dev,
		"axi %pap, axi offset %pap, pci %pap, res size %pap\n",
		&axi_addr, &ob->axi_offset, &pci_addr, &size);

	return ret;
}