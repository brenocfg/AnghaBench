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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct ice_pf {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* ICE_DDP_PKG_PATH ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_DSN ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static char *ice_get_opt_fw_name(struct ice_pf *pf)
{
	/* Optional firmware name same as default with additional dash
	 * followed by a EUI-64 identifier (PCIe Device Serial Number)
	 */
	struct pci_dev *pdev = pf->pdev;
	char *opt_fw_filename = NULL;
	u32 dword;
	u8 dsn[8];
	int pos;

	/* Determine the name of the optional file using the DSN (two
	 * dwords following the start of the DSN Capability).
	 */
	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_DSN);
	if (pos) {
		opt_fw_filename = kzalloc(NAME_MAX, GFP_KERNEL);
		if (!opt_fw_filename)
			return NULL;

		pci_read_config_dword(pdev, pos + 4, &dword);
		put_unaligned_le32(dword, &dsn[0]);
		pci_read_config_dword(pdev, pos + 8, &dword);
		put_unaligned_le32(dword, &dsn[4]);
		snprintf(opt_fw_filename, NAME_MAX,
			 "%sice-%02x%02x%02x%02x%02x%02x%02x%02x.pkg",
			 ICE_DDP_PKG_PATH,
			 dsn[7], dsn[6], dsn[5], dsn[4],
			 dsn[3], dsn[2], dsn[1], dsn[0]);
	}

	return opt_fw_filename;
}