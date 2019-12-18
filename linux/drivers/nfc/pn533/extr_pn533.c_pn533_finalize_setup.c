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
struct pn533_fw_version {int /*<<< orphan*/  rev; int /*<<< orphan*/  ver; int /*<<< orphan*/  ic; } ;
struct pn533 {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  fw_ver ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pn533_fw_version*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfc_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nfc_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pn533_get_firmware_version (struct pn533*,struct pn533_fw_version*) ; 
 int pn533_setup (struct pn533*) ; 

int pn533_finalize_setup(struct pn533 *dev)
{

	struct pn533_fw_version fw_ver;
	int rc;

	memset(&fw_ver, 0, sizeof(fw_ver));

	rc = pn533_get_firmware_version(dev, &fw_ver);
	if (rc) {
		nfc_err(dev->dev, "Unable to get FW version\n");
		return rc;
	}

	nfc_info(dev->dev, "NXP PN5%02X firmware ver %d.%d now attached\n",
		fw_ver.ic, fw_ver.ver, fw_ver.rev);

	rc = pn533_setup(dev);
	if (rc)
		return rc;

	return 0;
}