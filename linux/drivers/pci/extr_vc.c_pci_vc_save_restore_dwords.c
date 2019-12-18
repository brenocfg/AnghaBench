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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci_vc_save_restore_dwords(struct pci_dev *dev, int pos,
				       u32 *buf, int dwords, bool save)
{
	int i;

	for (i = 0; i < dwords; i++, buf++) {
		if (save)
			pci_read_config_dword(dev, pos + (i * 4), buf);
		else
			pci_write_config_dword(dev, pos + (i * 4), *buf);
	}
}