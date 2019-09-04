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
typedef  int uint32_t ;
struct fsi_master_acf {int trace_enabled; int /*<<< orphan*/  dev; scalar_t__ cf_mem; } ;

/* Variables and functions */
 int API_VERSION_MAJ ; 
 int ENODEV ; 
 int FW_OPTION_TRACE_EN ; 
 scalar_t__ HDR_API_VERS ; 
 scalar_t__ HDR_FW_OPTIONS ; 
 scalar_t__ HDR_FW_VERS ; 
 scalar_t__ HDR_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 int ioread16be (scalar_t__) ; 
 int ioread32be (scalar_t__) ; 

__attribute__((used)) static int check_firmware_image(struct fsi_master_acf *master)
{
	uint32_t fw_vers, fw_api, fw_options;

	fw_vers = ioread16be(master->cf_mem + HDR_OFFSET + HDR_FW_VERS);
	fw_api = ioread16be(master->cf_mem + HDR_OFFSET + HDR_API_VERS);
	fw_options = ioread32be(master->cf_mem + HDR_OFFSET + HDR_FW_OPTIONS);
	master->trace_enabled = !!(fw_options & FW_OPTION_TRACE_EN);

	/* Check version and signature */
	dev_info(master->dev, "ColdFire initialized, firmware v%d API v%d.%d (trace %s)\n",
		 fw_vers, fw_api >> 8, fw_api & 0xff,
		 master->trace_enabled ? "enabled" : "disabled");

	if ((fw_api >> 8) != API_VERSION_MAJ) {
		dev_err(master->dev, "Unsupported coprocessor API version !\n");
		return -ENODEV;
	}

	return 0;
}