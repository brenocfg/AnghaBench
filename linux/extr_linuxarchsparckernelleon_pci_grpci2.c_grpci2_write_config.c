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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {unsigned int number; } ;
struct grpci2_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCI_SLOT (unsigned int) ; 
 int grpci2_cfg_w16 (struct grpci2_priv*,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int grpci2_cfg_w32 (struct grpci2_priv*,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int grpci2_cfg_w8 (struct grpci2_priv*,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct grpci2_priv* grpci2priv ; 

__attribute__((used)) static int grpci2_write_config(struct pci_bus *bus, unsigned int devfn,
			       int where, int size, u32 val)
{
	struct grpci2_priv *priv = grpci2priv;
	unsigned int busno = bus->number;

	if (PCI_SLOT(devfn) > 15 || busno > 255)
		return 0;

#ifdef GRPCI2_DEBUG_CFGACCESS
	printk(KERN_INFO "grpci2_write_config: [%02x:%02x:%x] ofs=%d size=%d "
		"val=%x\n", busno, PCI_SLOT(devfn), PCI_FUNC(devfn),
		where, size, val);
#endif

	switch (size) {
	default:
		return -EINVAL;
	case 1:
		return grpci2_cfg_w8(priv, busno, devfn, where, val);
	case 2:
		return grpci2_cfg_w16(priv, busno, devfn, where, val);
	case 4:
		return grpci2_cfg_w32(priv, busno, devfn, where, val);
	}
}