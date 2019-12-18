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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {scalar_t__ cfg_size; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDOWN_PCI_ACCESS ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  pci_config_pm_runtime_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_config_pm_runtime_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_user_write_config_byte (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_user_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_user_write_config_word (struct pci_dev*,scalar_t__,int) ; 
 int security_locked_down (int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pci_write_config(struct file *filp, struct kobject *kobj,
				struct bin_attribute *bin_attr, char *buf,
				loff_t off, size_t count)
{
	struct pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));
	unsigned int size = count;
	loff_t init_off = off;
	u8 *data = (u8 *) buf;
	int ret;

	ret = security_locked_down(LOCKDOWN_PCI_ACCESS);
	if (ret)
		return ret;

	if (off > dev->cfg_size)
		return 0;
	if (off + count > dev->cfg_size) {
		size = dev->cfg_size - off;
		count = size;
	}

	pci_config_pm_runtime_get(dev);

	if ((off & 1) && size) {
		pci_user_write_config_byte(dev, off, data[off - init_off]);
		off++;
		size--;
	}

	if ((off & 3) && size > 2) {
		u16 val = data[off - init_off];
		val |= (u16) data[off - init_off + 1] << 8;
		pci_user_write_config_word(dev, off, val);
		off += 2;
		size -= 2;
	}

	while (size > 3) {
		u32 val = data[off - init_off];
		val |= (u32) data[off - init_off + 1] << 8;
		val |= (u32) data[off - init_off + 2] << 16;
		val |= (u32) data[off - init_off + 3] << 24;
		pci_user_write_config_dword(dev, off, val);
		off += 4;
		size -= 4;
	}

	if (size >= 2) {
		u16 val = data[off - init_off];
		val |= (u16) data[off - init_off + 1] << 8;
		pci_user_write_config_word(dev, off, val);
		off += 2;
		size -= 2;
	}

	if (size) {
		pci_user_write_config_byte(dev, off, data[off - init_off]);
		off++;
		--size;
	}

	pci_config_pm_runtime_put(dev);

	return count;
}