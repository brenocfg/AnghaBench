#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int rev; int /*<<< orphan*/  gen; } ;
struct amd_chipset_info {TYPE_2__ sb_type; TYPE_1__* smbus_dev; } ;
struct TYPE_3__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CHIPSET_BOLTON ; 
 int /*<<< orphan*/  AMD_CHIPSET_HUDSON2 ; 
 int /*<<< orphan*/  AMD_CHIPSET_SB600 ; 
 int /*<<< orphan*/  AMD_CHIPSET_SB700 ; 
 int /*<<< orphan*/  AMD_CHIPSET_SB800 ; 
 int /*<<< orphan*/  AMD_CHIPSET_TAISHAN ; 
 int /*<<< orphan*/  AMD_CHIPSET_UNKNOWN ; 
 int /*<<< orphan*/  AMD_CHIPSET_YANGTZE ; 
 int /*<<< orphan*/  NOT_AMD_CHIPSET ; 
 int PCI_DEVICE_ID_AMD_HUDSON2_SMBUS ; 
 int PCI_DEVICE_ID_ATI_SBX00_SMBUS ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_AMD ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_ATI ; 
 void* pci_get_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amd_chipset_sb_type_init(struct amd_chipset_info *pinfo)
{
	u8 rev = 0;
	pinfo->sb_type.gen = AMD_CHIPSET_UNKNOWN;

	pinfo->smbus_dev = pci_get_device(PCI_VENDOR_ID_ATI,
			PCI_DEVICE_ID_ATI_SBX00_SMBUS, NULL);
	if (pinfo->smbus_dev) {
		rev = pinfo->smbus_dev->revision;
		if (rev >= 0x10 && rev <= 0x1f)
			pinfo->sb_type.gen = AMD_CHIPSET_SB600;
		else if (rev >= 0x30 && rev <= 0x3f)
			pinfo->sb_type.gen = AMD_CHIPSET_SB700;
		else if (rev >= 0x40 && rev <= 0x4f)
			pinfo->sb_type.gen = AMD_CHIPSET_SB800;
	} else {
		pinfo->smbus_dev = pci_get_device(PCI_VENDOR_ID_AMD,
				PCI_DEVICE_ID_AMD_HUDSON2_SMBUS, NULL);

		if (pinfo->smbus_dev) {
			rev = pinfo->smbus_dev->revision;
			if (rev >= 0x11 && rev <= 0x14)
				pinfo->sb_type.gen = AMD_CHIPSET_HUDSON2;
			else if (rev >= 0x15 && rev <= 0x18)
				pinfo->sb_type.gen = AMD_CHIPSET_BOLTON;
			else if (rev >= 0x39 && rev <= 0x3a)
				pinfo->sb_type.gen = AMD_CHIPSET_YANGTZE;
		} else {
			pinfo->smbus_dev = pci_get_device(PCI_VENDOR_ID_AMD,
							  0x145c, NULL);
			if (pinfo->smbus_dev) {
				rev = pinfo->smbus_dev->revision;
				pinfo->sb_type.gen = AMD_CHIPSET_TAISHAN;
			} else {
				pinfo->sb_type.gen = NOT_AMD_CHIPSET;
				return 0;
			}
		}
	}
	pinfo->sb_type.rev = rev;
	return 1;
}