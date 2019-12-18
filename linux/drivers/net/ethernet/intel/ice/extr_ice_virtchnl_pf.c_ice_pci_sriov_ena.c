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
struct ice_pf {int num_vfs_supported; int /*<<< orphan*/  flags; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ICE_FLAG_SRIOV_CAPABLE ; 
 int /*<<< orphan*/  ICE_FLAG_SRIOV_ENA ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int ice_alloc_vfs (struct ice_pf*,int) ; 
 int /*<<< orphan*/  ice_free_vfs (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_pf_state_is_nominal (struct ice_pf*) ; 
 int pci_num_vf (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_pci_sriov_ena(struct ice_pf *pf, int num_vfs)
{
	int pre_existing_vfs = pci_num_vf(pf->pdev);
	struct device *dev = &pf->pdev->dev;
	int err;

	if (!ice_pf_state_is_nominal(pf)) {
		dev_err(dev, "Cannot enable SR-IOV, device not ready\n");
		return -EBUSY;
	}

	if (!test_bit(ICE_FLAG_SRIOV_CAPABLE, pf->flags)) {
		dev_err(dev, "This device is not capable of SR-IOV\n");
		return -ENODEV;
	}

	if (pre_existing_vfs && pre_existing_vfs != num_vfs)
		ice_free_vfs(pf);
	else if (pre_existing_vfs && pre_existing_vfs == num_vfs)
		return num_vfs;

	if (num_vfs > pf->num_vfs_supported) {
		dev_err(dev, "Can't enable %d VFs, max VFs supported is %d\n",
			num_vfs, pf->num_vfs_supported);
		return -ENOTSUPP;
	}

	dev_info(dev, "Allocating %d VFs\n", num_vfs);
	err = ice_alloc_vfs(pf, num_vfs);
	if (err) {
		dev_err(dev, "Failed to enable SR-IOV: %d\n", err);
		return err;
	}

	set_bit(ICE_FLAG_SRIOV_ENA, pf->flags);
	return num_vfs;
}