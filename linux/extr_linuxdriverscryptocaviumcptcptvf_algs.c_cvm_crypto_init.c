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
typedef  size_t u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_vf {struct pci_dev* pdev; } ;
struct TYPE_2__ {size_t dev_count; struct cpt_vf** cdev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cav_register_algs () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ dev_handle ; 

int cvm_crypto_init(struct cpt_vf *cptvf)
{
	struct pci_dev *pdev = cptvf->pdev;
	u32 dev_count;

	dev_count = dev_handle.dev_count;
	dev_handle.cdev[dev_count] = cptvf;
	dev_handle.dev_count++;

	if (dev_count == 3) {
		if (cav_register_algs()) {
			dev_err(&pdev->dev, "Error in registering crypto algorithms\n");
			return -EINVAL;
		}
	}

	return 0;
}