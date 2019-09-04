#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int family; TYPE_1__* smc_fw; TYPE_1__* rlc_fw; TYPE_1__* me_fw; TYPE_1__* pfp_fw; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_3__ {size_t size; } ;

/* Variables and functions */
 size_t ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CEDAR_SMC_UCODE_SIZE ; 
#define  CHIP_CEDAR 147 
#define  CHIP_CYPRESS 146 
#define  CHIP_HEMLOCK 145 
#define  CHIP_JUNIPER 144 
#define  CHIP_PALM 143 
#define  CHIP_R600 142 
#define  CHIP_REDWOOD 141 
#define  CHIP_RS780 140 
#define  CHIP_RS880 139 
#define  CHIP_RV610 138 
#define  CHIP_RV620 137 
#define  CHIP_RV630 136 
#define  CHIP_RV635 135 
#define  CHIP_RV670 134 
#define  CHIP_RV710 133 
#define  CHIP_RV730 132 
#define  CHIP_RV740 131 
#define  CHIP_RV770 130 
#define  CHIP_SUMO 129 
#define  CHIP_SUMO2 128 
 int /*<<< orphan*/  CYPRESS_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,char const*) ; 
 int EINVAL ; 
 int EVERGREEN_PFP_UCODE_SIZE ; 
 int EVERGREEN_PM4_UCODE_SIZE ; 
 int EVERGREEN_RLC_UCODE_SIZE ; 
 int /*<<< orphan*/  JUNIPER_SMC_UCODE_SIZE ; 
 int R600_PFP_UCODE_SIZE ; 
 int R600_PM4_UCODE_SIZE ; 
 int R600_RLC_UCODE_SIZE ; 
 int R700_PFP_UCODE_SIZE ; 
 int R700_PM4_UCODE_SIZE ; 
 int R700_RLC_UCODE_SIZE ; 
 int /*<<< orphan*/  REDWOOD_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  RV710_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  RV730_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  RV740_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  RV770_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  release_firmware (TYPE_1__*) ; 
 int request_firmware (TYPE_1__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

int r600_init_microcode(struct radeon_device *rdev)
{
	const char *chip_name;
	const char *rlc_chip_name;
	const char *smc_chip_name = "RV770";
	size_t pfp_req_size, me_req_size, rlc_req_size, smc_req_size = 0;
	char fw_name[30];
	int err;

	DRM_DEBUG("\n");

	switch (rdev->family) {
	case CHIP_R600:
		chip_name = "R600";
		rlc_chip_name = "R600";
		break;
	case CHIP_RV610:
		chip_name = "RV610";
		rlc_chip_name = "R600";
		break;
	case CHIP_RV630:
		chip_name = "RV630";
		rlc_chip_name = "R600";
		break;
	case CHIP_RV620:
		chip_name = "RV620";
		rlc_chip_name = "R600";
		break;
	case CHIP_RV635:
		chip_name = "RV635";
		rlc_chip_name = "R600";
		break;
	case CHIP_RV670:
		chip_name = "RV670";
		rlc_chip_name = "R600";
		break;
	case CHIP_RS780:
	case CHIP_RS880:
		chip_name = "RS780";
		rlc_chip_name = "R600";
		break;
	case CHIP_RV770:
		chip_name = "RV770";
		rlc_chip_name = "R700";
		smc_chip_name = "RV770";
		smc_req_size = ALIGN(RV770_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_RV730:
		chip_name = "RV730";
		rlc_chip_name = "R700";
		smc_chip_name = "RV730";
		smc_req_size = ALIGN(RV730_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_RV710:
		chip_name = "RV710";
		rlc_chip_name = "R700";
		smc_chip_name = "RV710";
		smc_req_size = ALIGN(RV710_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_RV740:
		chip_name = "RV730";
		rlc_chip_name = "R700";
		smc_chip_name = "RV740";
		smc_req_size = ALIGN(RV740_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_CEDAR:
		chip_name = "CEDAR";
		rlc_chip_name = "CEDAR";
		smc_chip_name = "CEDAR";
		smc_req_size = ALIGN(CEDAR_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_REDWOOD:
		chip_name = "REDWOOD";
		rlc_chip_name = "REDWOOD";
		smc_chip_name = "REDWOOD";
		smc_req_size = ALIGN(REDWOOD_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_JUNIPER:
		chip_name = "JUNIPER";
		rlc_chip_name = "JUNIPER";
		smc_chip_name = "JUNIPER";
		smc_req_size = ALIGN(JUNIPER_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_CYPRESS:
	case CHIP_HEMLOCK:
		chip_name = "CYPRESS";
		rlc_chip_name = "CYPRESS";
		smc_chip_name = "CYPRESS";
		smc_req_size = ALIGN(CYPRESS_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_PALM:
		chip_name = "PALM";
		rlc_chip_name = "SUMO";
		break;
	case CHIP_SUMO:
		chip_name = "SUMO";
		rlc_chip_name = "SUMO";
		break;
	case CHIP_SUMO2:
		chip_name = "SUMO2";
		rlc_chip_name = "SUMO";
		break;
	default: BUG();
	}

	if (rdev->family >= CHIP_CEDAR) {
		pfp_req_size = EVERGREEN_PFP_UCODE_SIZE * 4;
		me_req_size = EVERGREEN_PM4_UCODE_SIZE * 4;
		rlc_req_size = EVERGREEN_RLC_UCODE_SIZE * 4;
	} else if (rdev->family >= CHIP_RV770) {
		pfp_req_size = R700_PFP_UCODE_SIZE * 4;
		me_req_size = R700_PM4_UCODE_SIZE * 4;
		rlc_req_size = R700_RLC_UCODE_SIZE * 4;
	} else {
		pfp_req_size = R600_PFP_UCODE_SIZE * 4;
		me_req_size = R600_PM4_UCODE_SIZE * 12;
		rlc_req_size = R600_RLC_UCODE_SIZE * 4;
	}

	DRM_INFO("Loading %s Microcode\n", chip_name);

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_pfp.bin", chip_name);
	err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
	if (err)
		goto out;
	if (rdev->pfp_fw->size != pfp_req_size) {
		pr_err("r600_cp: Bogus length %zu in firmware \"%s\"\n",
		       rdev->pfp_fw->size, fw_name);
		err = -EINVAL;
		goto out;
	}

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_me.bin", chip_name);
	err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
	if (err)
		goto out;
	if (rdev->me_fw->size != me_req_size) {
		pr_err("r600_cp: Bogus length %zu in firmware \"%s\"\n",
		       rdev->me_fw->size, fw_name);
		err = -EINVAL;
	}

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_rlc.bin", rlc_chip_name);
	err = request_firmware(&rdev->rlc_fw, fw_name, rdev->dev);
	if (err)
		goto out;
	if (rdev->rlc_fw->size != rlc_req_size) {
		pr_err("r600_rlc: Bogus length %zu in firmware \"%s\"\n",
		       rdev->rlc_fw->size, fw_name);
		err = -EINVAL;
	}

	if ((rdev->family >= CHIP_RV770) && (rdev->family <= CHIP_HEMLOCK)) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_smc.bin", smc_chip_name);
		err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
		if (err) {
			pr_err("smc: error loading firmware \"%s\"\n", fw_name);
			release_firmware(rdev->smc_fw);
			rdev->smc_fw = NULL;
			err = 0;
		} else if (rdev->smc_fw->size != smc_req_size) {
			pr_err("smc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->smc_fw->size, fw_name);
			err = -EINVAL;
		}
	}

out:
	if (err) {
		if (err != -EINVAL)
			pr_err("r600_cp: Failed to load firmware \"%s\"\n",
			       fw_name);
		release_firmware(rdev->pfp_fw);
		rdev->pfp_fw = NULL;
		release_firmware(rdev->me_fw);
		rdev->me_fw = NULL;
		release_firmware(rdev->rlc_fw);
		rdev->rlc_fw = NULL;
		release_firmware(rdev->smc_fw);
		rdev->smc_fw = NULL;
	}
	return err;
}