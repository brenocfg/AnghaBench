#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int* model; int* board_model; int* version; int* local_mac; int mac_num; int* phy_type; } ;
struct niu {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; TYPE_1__ vpd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 unsigned int FOUND_MASK_ALL ; 
 unsigned int FOUND_MASK_BMODEL ; 
 unsigned int FOUND_MASK_MAC ; 
 unsigned int FOUND_MASK_MODEL ; 
 unsigned int FOUND_MASK_NMAC ; 
 unsigned int FOUND_MASK_PHY ; 
 unsigned int FOUND_MASK_VERS ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int NIU_VPD_BD_MODEL_MAX ; 
 int NIU_VPD_MODEL_MAX ; 
 int NIU_VPD_PHY_TYPE_MAX ; 
 int NIU_VPD_VERSION_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  netif_printk (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int niu_pci_eeprom_read (struct niu*,scalar_t__) ; 
 int niu_pci_vpd_get_propname (struct niu*,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  niu_vpd_parse_version (struct niu*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int niu_pci_vpd_scan_props(struct niu *np, u32 start, u32 end)
{
	unsigned int found_mask = 0;
#define FOUND_MASK_MODEL	0x00000001
#define FOUND_MASK_BMODEL	0x00000002
#define FOUND_MASK_VERS		0x00000004
#define FOUND_MASK_MAC		0x00000008
#define FOUND_MASK_NMAC		0x00000010
#define FOUND_MASK_PHY		0x00000020
#define FOUND_MASK_ALL		0x0000003f

	netif_printk(np, probe, KERN_DEBUG, np->dev,
		     "VPD_SCAN: start[%x] end[%x]\n", start, end);
	while (start < end) {
		int len, err, prop_len;
		char namebuf[64];
		u8 *prop_buf;
		int max_len;

		if (found_mask == FOUND_MASK_ALL) {
			niu_vpd_parse_version(np);
			return 1;
		}

		err = niu_pci_eeprom_read(np, start + 2);
		if (err < 0)
			return err;
		len = err;
		start += 3;

		prop_len = niu_pci_eeprom_read(np, start + 4);
		if (prop_len < 0)
			return prop_len;
		err = niu_pci_vpd_get_propname(np, start + 5, namebuf, 64);
		if (err < 0)
			return err;

		prop_buf = NULL;
		max_len = 0;
		if (!strcmp(namebuf, "model")) {
			prop_buf = np->vpd.model;
			max_len = NIU_VPD_MODEL_MAX;
			found_mask |= FOUND_MASK_MODEL;
		} else if (!strcmp(namebuf, "board-model")) {
			prop_buf = np->vpd.board_model;
			max_len = NIU_VPD_BD_MODEL_MAX;
			found_mask |= FOUND_MASK_BMODEL;
		} else if (!strcmp(namebuf, "version")) {
			prop_buf = np->vpd.version;
			max_len = NIU_VPD_VERSION_MAX;
			found_mask |= FOUND_MASK_VERS;
		} else if (!strcmp(namebuf, "local-mac-address")) {
			prop_buf = np->vpd.local_mac;
			max_len = ETH_ALEN;
			found_mask |= FOUND_MASK_MAC;
		} else if (!strcmp(namebuf, "num-mac-addresses")) {
			prop_buf = &np->vpd.mac_num;
			max_len = 1;
			found_mask |= FOUND_MASK_NMAC;
		} else if (!strcmp(namebuf, "phy-type")) {
			prop_buf = np->vpd.phy_type;
			max_len = NIU_VPD_PHY_TYPE_MAX;
			found_mask |= FOUND_MASK_PHY;
		}

		if (max_len && prop_len > max_len) {
			dev_err(np->device, "Property '%s' length (%d) is too long\n", namebuf, prop_len);
			return -EINVAL;
		}

		if (prop_buf) {
			u32 off = start + 5 + err;
			int i;

			netif_printk(np, probe, KERN_DEBUG, np->dev,
				     "VPD_SCAN: Reading in property [%s] len[%d]\n",
				     namebuf, prop_len);
			for (i = 0; i < prop_len; i++) {
				err = niu_pci_eeprom_read(np, off + i);
				if (err >= 0)
					*prop_buf = err;
				++prop_buf;
			}
		}

		start += len;
	}

	return 0;
}