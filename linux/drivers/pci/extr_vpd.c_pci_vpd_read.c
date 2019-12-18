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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_vpd {int valid; scalar_t__ len; int busy; int /*<<< orphan*/  lock; scalar_t__ cap; int /*<<< orphan*/  flag; } ;
struct pci_dev {struct pci_vpd* vpd; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ PCI_VPD_ADDR ; 
 int /*<<< orphan*/  PCI_VPD_ADDR_F ; 
 scalar_t__ PCI_VPD_DATA ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pci_user_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int pci_user_write_config_word (struct pci_dev*,scalar_t__,scalar_t__) ; 
 scalar_t__ pci_vpd_size (struct pci_dev*,scalar_t__) ; 
 int pci_vpd_wait (struct pci_dev*) ; 

__attribute__((used)) static ssize_t pci_vpd_read(struct pci_dev *dev, loff_t pos, size_t count,
			    void *arg)
{
	struct pci_vpd *vpd = dev->vpd;
	int ret;
	loff_t end = pos + count;
	u8 *buf = arg;

	if (pos < 0)
		return -EINVAL;

	if (!vpd->valid) {
		vpd->valid = 1;
		vpd->len = pci_vpd_size(dev, vpd->len);
	}

	if (vpd->len == 0)
		return -EIO;

	if (pos > vpd->len)
		return 0;

	if (end > vpd->len) {
		end = vpd->len;
		count = end - pos;
	}

	if (mutex_lock_killable(&vpd->lock))
		return -EINTR;

	ret = pci_vpd_wait(dev);
	if (ret < 0)
		goto out;

	while (pos < end) {
		u32 val;
		unsigned int i, skip;

		ret = pci_user_write_config_word(dev, vpd->cap + PCI_VPD_ADDR,
						 pos & ~3);
		if (ret < 0)
			break;
		vpd->busy = 1;
		vpd->flag = PCI_VPD_ADDR_F;
		ret = pci_vpd_wait(dev);
		if (ret < 0)
			break;

		ret = pci_user_read_config_dword(dev, vpd->cap + PCI_VPD_DATA, &val);
		if (ret < 0)
			break;

		skip = pos & 3;
		for (i = 0;  i < sizeof(u32); i++) {
			if (i >= skip) {
				*buf++ = val;
				if (++pos == end)
					break;
			}
			val >>= 8;
		}
	}
out:
	mutex_unlock(&vpd->lock);
	return ret ? ret : count;
}