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
struct ice_pf {TYPE_1__* pdev; } ;
struct firmware {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DDP_PKG_FILE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int firmware_request_nowarn (struct firmware const**,char*,struct device*) ; 
 char* ice_get_opt_fw_name (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_load_pkg (struct firmware const*,struct ice_pf*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static void ice_request_fw(struct ice_pf *pf)
{
	char *opt_fw_filename = ice_get_opt_fw_name(pf);
	const struct firmware *firmware = NULL;
	struct device *dev = &pf->pdev->dev;
	int err = 0;

	/* optional device-specific DDP (if present) overrides the default DDP
	 * package file. kernel logs a debug message if the file doesn't exist,
	 * and warning messages for other errors.
	 */
	if (opt_fw_filename) {
		err = firmware_request_nowarn(&firmware, opt_fw_filename, dev);
		if (err) {
			kfree(opt_fw_filename);
			goto dflt_pkg_load;
		}

		/* request for firmware was successful. Download to device */
		ice_load_pkg(firmware, pf);
		kfree(opt_fw_filename);
		release_firmware(firmware);
		return;
	}

dflt_pkg_load:
	err = request_firmware(&firmware, ICE_DDP_PKG_FILE, dev);
	if (err) {
		dev_err(dev,
			"The DDP package file was not found or could not be read. Entering Safe Mode\n");
		return;
	}

	/* request for firmware was successful. Download to device */
	ice_load_pkg(firmware, pf);
	release_firmware(firmware);
}