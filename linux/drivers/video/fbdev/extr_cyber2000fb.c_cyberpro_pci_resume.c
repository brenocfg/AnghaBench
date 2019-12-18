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
struct cfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cyberpro_common_resume (struct cfb_info*) ; 
 int /*<<< orphan*/  cyberpro_pci_enable_mmio (struct cfb_info*) ; 
 struct cfb_info* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static int cyberpro_pci_resume(struct pci_dev *dev)
{
	struct cfb_info *cfb = pci_get_drvdata(dev);

	if (cfb) {
		cyberpro_pci_enable_mmio(cfb);
		cyberpro_common_resume(cfb);
	}

	return 0;
}