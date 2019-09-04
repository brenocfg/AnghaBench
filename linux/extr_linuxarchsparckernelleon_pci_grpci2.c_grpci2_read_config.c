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
 int grpci2_cfg_r16 (struct grpci2_priv*,unsigned int,unsigned int,int,int /*<<< orphan*/ *) ; 
 int grpci2_cfg_r32 (struct grpci2_priv*,unsigned int,unsigned int,int,int /*<<< orphan*/ *) ; 
 int grpci2_cfg_r8 (struct grpci2_priv*,unsigned int,unsigned int,int,int /*<<< orphan*/ *) ; 
 struct grpci2_priv* grpci2priv ; 

__attribute__((used)) static int grpci2_read_config(struct pci_bus *bus, unsigned int devfn,
			      int where, int size, u32 *val)
{
	struct grpci2_priv *priv = grpci2priv;
	unsigned int busno = bus->number;
	int ret;

	if (PCI_SLOT(devfn) > 15 || busno > 255) {
		*val = ~0;
		return 0;
	}

	switch (size) {
	case 1:
		ret = grpci2_cfg_r8(priv, busno, devfn, where, val);
		break;
	case 2:
		ret = grpci2_cfg_r16(priv, busno, devfn, where, val);
		break;
	case 4:
		ret = grpci2_cfg_r32(priv, busno, devfn, where, val);
		break;
	default:
		ret = -EINVAL;
		break;
	}

#ifdef GRPCI2_DEBUG_CFGACCESS
	printk(KERN_INFO "grpci2_read_config: [%02x:%02x:%x] ofs=%d val=%x "
		"size=%d\n", busno, PCI_SLOT(devfn), PCI_FUNC(devfn), where,
		*val, size);
#endif

	return ret;
}