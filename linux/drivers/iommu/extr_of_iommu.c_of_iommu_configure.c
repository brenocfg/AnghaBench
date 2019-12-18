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
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct of_pci_iommu_alias_info {struct device_node* np; struct device* dev; } ;
typedef  struct iommu_ops const iommu_ops ;
struct iommu_fwspec {struct iommu_ops const* ops; } ;
struct device_node {int dummy; } ;
struct device {scalar_t__ bus; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 struct iommu_ops const* ERR_PTR (int) ; 
 int NO_IOMMU ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 scalar_t__ dev_is_fsl_mc (struct device*) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  device_iommu_mapped (struct device*) ; 
 int /*<<< orphan*/  iommu_fwspec_free (struct device*) ; 
 int iommu_probe_device (struct device*) ; 
 int of_fsl_mc_iommu_init (int /*<<< orphan*/ ,struct device_node*) ; 
 int of_iommu_xlate (struct device*,struct of_phandle_args*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 int /*<<< orphan*/  of_pci_iommu_init ; 
 int pci_for_each_dma_alias (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct of_pci_iommu_alias_info*) ; 
 int /*<<< orphan*/  to_fsl_mc_device (struct device*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

const struct iommu_ops *of_iommu_configure(struct device *dev,
					   struct device_node *master_np)
{
	const struct iommu_ops *ops = NULL;
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	int err = NO_IOMMU;

	if (!master_np)
		return NULL;

	if (fwspec) {
		if (fwspec->ops)
			return fwspec->ops;

		/* In the deferred case, start again from scratch */
		iommu_fwspec_free(dev);
	}

	/*
	 * We don't currently walk up the tree looking for a parent IOMMU.
	 * See the `Notes:' section of
	 * Documentation/devicetree/bindings/iommu/iommu.txt
	 */
	if (dev_is_pci(dev)) {
		struct of_pci_iommu_alias_info info = {
			.dev = dev,
			.np = master_np,
		};

		err = pci_for_each_dma_alias(to_pci_dev(dev),
					     of_pci_iommu_init, &info);
	} else if (dev_is_fsl_mc(dev)) {
		err = of_fsl_mc_iommu_init(to_fsl_mc_device(dev), master_np);
	} else {
		struct of_phandle_args iommu_spec;
		int idx = 0;

		while (!of_parse_phandle_with_args(master_np, "iommus",
						   "#iommu-cells",
						   idx, &iommu_spec)) {
			err = of_iommu_xlate(dev, &iommu_spec);
			of_node_put(iommu_spec.np);
			idx++;
			if (err)
				break;
		}
	}


	/*
	 * Two success conditions can be represented by non-negative err here:
	 * >0 : there is no IOMMU, or one was unavailable for non-fatal reasons
	 *  0 : we found an IOMMU, and dev->fwspec is initialised appropriately
	 * <0 : any actual error
	 */
	if (!err) {
		/* The fwspec pointer changed, read it again */
		fwspec = dev_iommu_fwspec_get(dev);
		ops    = fwspec->ops;
	}
	/*
	 * If we have reason to believe the IOMMU driver missed the initial
	 * probe for dev, replay it to get things in order.
	 */
	if (!err && dev->bus && !device_iommu_mapped(dev))
		err = iommu_probe_device(dev);

	/* Ignore all other errors apart from EPROBE_DEFER */
	if (err == -EPROBE_DEFER) {
		ops = ERR_PTR(err);
	} else if (err < 0) {
		dev_dbg(dev, "Adding to IOMMU failed: %d\n", err);
		ops = NULL;
	}

	return ops;
}