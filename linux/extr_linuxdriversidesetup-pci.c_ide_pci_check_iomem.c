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
typedef  int ulong ;
struct pci_dev {int dummy; } ;
struct ide_port_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IORESOURCE_IO ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int) ; 

__attribute__((used)) static int ide_pci_check_iomem(struct pci_dev *dev, const struct ide_port_info *d,
			       int bar)
{
	ulong flags = pci_resource_flags(dev, bar);

	/* Unconfigured ? */
	if (!flags || pci_resource_len(dev, bar) == 0)
		return 0;

	/* I/O space */
	if (flags & IORESOURCE_IO)
		return 0;

	/* Bad */
	return -EINVAL;
}