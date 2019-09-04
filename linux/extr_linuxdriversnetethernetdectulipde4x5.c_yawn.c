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
typedef  int /*<<< orphan*/  u_long ;
struct pci_dev {int dummy; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct de4x5_private {scalar_t__ chipset; scalar_t__ bus; int /*<<< orphan*/  gendev; } ;

/* Variables and functions */
 scalar_t__ DC21040 ; 
 scalar_t__ DC21140 ; 
 int /*<<< orphan*/  DE4X5_SICR ; 
 scalar_t__ EISA ; 
 int /*<<< orphan*/  PCI_CFDA_PSM ; 
 int /*<<< orphan*/  PCI_CFPM ; 
#define  SLEEP 130 
#define  SNOOZE 129 
#define  WAKEUP 128 
 int /*<<< orphan*/  mdelay (int) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int const) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
yawn(struct net_device *dev, int state)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;

    if ((lp->chipset == DC21040) || (lp->chipset == DC21140)) return;

    if(lp->bus == EISA) {
	switch(state) {
	  case WAKEUP:
	    outb(WAKEUP, PCI_CFPM);
	    mdelay(10);
	    break;

	  case SNOOZE:
	    outb(SNOOZE, PCI_CFPM);
	    break;

	  case SLEEP:
	    outl(0, DE4X5_SICR);
	    outb(SLEEP, PCI_CFPM);
	    break;
	}
    } else {
	struct pci_dev *pdev = to_pci_dev (lp->gendev);
	switch(state) {
	  case WAKEUP:
	    pci_write_config_byte(pdev, PCI_CFDA_PSM, WAKEUP);
	    mdelay(10);
	    break;

	  case SNOOZE:
	    pci_write_config_byte(pdev, PCI_CFDA_PSM, SNOOZE);
	    break;

	  case SLEEP:
	    outl(0, DE4X5_SICR);
	    pci_write_config_byte(pdev, PCI_CFDA_PSM, SLEEP);
	    break;
	}
    }
}