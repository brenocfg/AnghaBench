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
struct cfb_info {int /*<<< orphan*/  region; } ;

/* Variables and functions */
 int /*<<< orphan*/  cyberpro_common_remove (struct cfb_info*) ; 
 int /*<<< orphan*/  cyberpro_free_fb_info (struct cfb_info*) ; 
 struct cfb_info* int_cfb_info ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct cfb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void cyberpro_pci_remove(struct pci_dev *dev)
{
	struct cfb_info *cfb = pci_get_drvdata(dev);

	if (cfb) {
		cyberpro_common_remove(cfb);
		iounmap(cfb->region);
		cyberpro_free_fb_info(cfb);

		if (cfb == int_cfb_info)
			int_cfb_info = NULL;

		pci_release_regions(dev);
	}
}