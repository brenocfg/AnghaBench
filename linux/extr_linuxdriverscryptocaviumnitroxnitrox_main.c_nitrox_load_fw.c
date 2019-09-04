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
struct ucode {int /*<<< orphan*/  version; } ;
struct TYPE_2__ {char* fw_name; } ;
struct nitrox_device {int /*<<< orphan*/  status; TYPE_1__ hw; } ;
struct firmware {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int /*<<< orphan*/  NITROX_UCODE_LOADED ; 
 int VERSION_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  write_to_ucd_unit (struct nitrox_device*,struct ucode*) ; 

__attribute__((used)) static int nitrox_load_fw(struct nitrox_device *ndev, const char *fw_name)
{
	const struct firmware *fw;
	struct ucode *ucode;
	int ret;

	dev_info(DEV(ndev), "Loading firmware \"%s\"\n", fw_name);

	ret = request_firmware(&fw, fw_name, DEV(ndev));
	if (ret < 0) {
		dev_err(DEV(ndev), "failed to get firmware %s\n", fw_name);
		return ret;
	}

	ucode = (struct ucode *)fw->data;
	/* copy the firmware version */
	memcpy(ndev->hw.fw_name, ucode->version, (VERSION_LEN - 2));
	ndev->hw.fw_name[VERSION_LEN - 1] = '\0';

	write_to_ucd_unit(ndev, ucode);
	release_firmware(fw);

	set_bit(NITROX_UCODE_LOADED, &ndev->status);
	/* barrier to sync with other cpus */
	smp_mb__after_atomic();
	return 0;
}