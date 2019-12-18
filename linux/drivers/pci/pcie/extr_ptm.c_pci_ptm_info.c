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
struct pci_dev {int ptm_granularity; scalar_t__ ptm_root; } ;
typedef  int /*<<< orphan*/  clock_desc ;

/* Variables and functions */
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void pci_ptm_info(struct pci_dev *dev)
{
	char clock_desc[8];

	switch (dev->ptm_granularity) {
	case 0:
		snprintf(clock_desc, sizeof(clock_desc), "unknown");
		break;
	case 255:
		snprintf(clock_desc, sizeof(clock_desc), ">254ns");
		break;
	default:
		snprintf(clock_desc, sizeof(clock_desc), "%udns",
			 dev->ptm_granularity);
		break;
	}
	pci_info(dev, "PTM enabled%s, %s granularity\n",
		 dev->ptm_root ? " (root)" : "", clock_desc);
}