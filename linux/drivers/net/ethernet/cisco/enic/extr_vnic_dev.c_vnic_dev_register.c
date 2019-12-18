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
struct vnic_dev_bar {int dummy; } ;
struct vnic_dev {struct pci_dev* pdev; void* priv; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vnic_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vnic_dev_discover_res (struct vnic_dev*,struct vnic_dev_bar*,unsigned int) ; 
 int /*<<< orphan*/  vnic_dev_unregister (struct vnic_dev*) ; 

struct vnic_dev *vnic_dev_register(struct vnic_dev *vdev,
	void *priv, struct pci_dev *pdev, struct vnic_dev_bar *bar,
	unsigned int num_bars)
{
	if (!vdev) {
		vdev = kzalloc(sizeof(struct vnic_dev), GFP_KERNEL);
		if (!vdev)
			return NULL;
	}

	vdev->priv = priv;
	vdev->pdev = pdev;

	if (vnic_dev_discover_res(vdev, bar, num_bars))
		goto err_out;

	return vdev;

err_out:
	vnic_dev_unregister(vdev);
	return NULL;
}