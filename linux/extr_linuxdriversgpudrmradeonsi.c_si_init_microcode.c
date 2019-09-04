#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {int family; int new_fw; TYPE_2__* smc_fw; TYPE_2__* mc_fw; TYPE_2__* rlc_fw; TYPE_2__* ce_fw; TYPE_2__* me_fw; TYPE_2__* pfp_fw; int /*<<< orphan*/  dev; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_6__ {size_t size; } ;
struct TYPE_5__ {int revision; int device; } ;

/* Variables and functions */
 size_t ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_HAINAN 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,char const*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HAINAN_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  MC_SEQ_MISC0 ; 
 int OLAND_MC_UCODE_SIZE ; 
 int /*<<< orphan*/  OLAND_SMC_UCODE_SIZE ; 
 int PITCAIRN_MC_UCODE_SIZE ; 
 int /*<<< orphan*/  PITCAIRN_SMC_UCODE_SIZE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SI_CE_UCODE_SIZE ; 
 int SI_MC_UCODE_SIZE ; 
 int SI_PFP_UCODE_SIZE ; 
 int SI_PM4_UCODE_SIZE ; 
 int SI_RLC_UCODE_SIZE ; 
 int TAHITI_MC_UCODE_SIZE ; 
 int /*<<< orphan*/  TAHITI_SMC_UCODE_SIZE ; 
 int VERDE_MC_UCODE_SIZE ; 
 int /*<<< orphan*/  VERDE_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int radeon_ucode_validate (TYPE_2__*) ; 
 int /*<<< orphan*/  release_firmware (TYPE_2__*) ; 
 int request_firmware (TYPE_2__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int si_init_microcode(struct radeon_device *rdev)
{
	const char *chip_name;
	const char *new_chip_name;
	size_t pfp_req_size, me_req_size, ce_req_size, rlc_req_size, mc_req_size;
	size_t smc_req_size, mc2_req_size;
	char fw_name[30];
	int err;
	int new_fw = 0;
	bool new_smc = false;
	bool si58_fw = false;
	bool banks2_fw = false;

	DRM_DEBUG("\n");

	switch (rdev->family) {
	case CHIP_TAHITI:
		chip_name = "TAHITI";
		new_chip_name = "tahiti";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = SI_MC_UCODE_SIZE * 4;
		mc2_req_size = TAHITI_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(TAHITI_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_PITCAIRN:
		chip_name = "PITCAIRN";
		if ((rdev->pdev->revision == 0x81) &&
		    ((rdev->pdev->device == 0x6810) ||
		     (rdev->pdev->device == 0x6811)))
			new_smc = true;
		new_chip_name = "pitcairn";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = SI_MC_UCODE_SIZE * 4;
		mc2_req_size = PITCAIRN_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(PITCAIRN_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_VERDE:
		chip_name = "VERDE";
		if (((rdev->pdev->device == 0x6820) &&
		     ((rdev->pdev->revision == 0x81) ||
		      (rdev->pdev->revision == 0x83))) ||
		    ((rdev->pdev->device == 0x6821) &&
		     ((rdev->pdev->revision == 0x83) ||
		      (rdev->pdev->revision == 0x87))) ||
		    ((rdev->pdev->revision == 0x87) &&
		     ((rdev->pdev->device == 0x6823) ||
		      (rdev->pdev->device == 0x682b))))
			new_smc = true;
		new_chip_name = "verde";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = SI_MC_UCODE_SIZE * 4;
		mc2_req_size = VERDE_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(VERDE_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_OLAND:
		chip_name = "OLAND";
		if (((rdev->pdev->revision == 0x81) &&
		     ((rdev->pdev->device == 0x6600) ||
		      (rdev->pdev->device == 0x6604) ||
		      (rdev->pdev->device == 0x6605) ||
		      (rdev->pdev->device == 0x6610))) ||
		    ((rdev->pdev->revision == 0x83) &&
		     (rdev->pdev->device == 0x6610)))
			new_smc = true;
		new_chip_name = "oland";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = mc2_req_size = OLAND_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(OLAND_SMC_UCODE_SIZE, 4);
		break;
	case CHIP_HAINAN:
		chip_name = "HAINAN";
		if (((rdev->pdev->revision == 0x81) &&
		     (rdev->pdev->device == 0x6660)) ||
		    ((rdev->pdev->revision == 0x83) &&
		     ((rdev->pdev->device == 0x6660) ||
		      (rdev->pdev->device == 0x6663) ||
		      (rdev->pdev->device == 0x6665) ||
		      (rdev->pdev->device == 0x6667))))
			new_smc = true;
		else if ((rdev->pdev->revision == 0xc3) &&
			 (rdev->pdev->device == 0x6665))
			banks2_fw = true;
		new_chip_name = "hainan";
		pfp_req_size = SI_PFP_UCODE_SIZE * 4;
		me_req_size = SI_PM4_UCODE_SIZE * 4;
		ce_req_size = SI_CE_UCODE_SIZE * 4;
		rlc_req_size = SI_RLC_UCODE_SIZE * 4;
		mc_req_size = mc2_req_size = OLAND_MC_UCODE_SIZE * 4;
		smc_req_size = ALIGN(HAINAN_SMC_UCODE_SIZE, 4);
		break;
	default: BUG();
	}

	/* this memory configuration requires special firmware */
	if (((RREG32(MC_SEQ_MISC0) & 0xff000000) >> 24) == 0x58)
		si58_fw = true;

	DRM_INFO("Loading %s Microcode\n", new_chip_name);

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_pfp.bin", new_chip_name);
	err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
	if (err) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_pfp.bin", chip_name);
		err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
		if (err)
			goto out;
		if (rdev->pfp_fw->size != pfp_req_size) {
			pr_err("si_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->pfp_fw->size, fw_name);
			err = -EINVAL;
			goto out;
		}
	} else {
		err = radeon_ucode_validate(rdev->pfp_fw);
		if (err) {
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_me.bin", new_chip_name);
	err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
	if (err) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_me.bin", chip_name);
		err = request_firmware(&rdev->me_fw, fw_name, rdev->dev);
		if (err)
			goto out;
		if (rdev->me_fw->size != me_req_size) {
			pr_err("si_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->me_fw->size, fw_name);
			err = -EINVAL;
		}
	} else {
		err = radeon_ucode_validate(rdev->me_fw);
		if (err) {
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_ce.bin", new_chip_name);
	err = request_firmware(&rdev->ce_fw, fw_name, rdev->dev);
	if (err) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_ce.bin", chip_name);
		err = request_firmware(&rdev->ce_fw, fw_name, rdev->dev);
		if (err)
			goto out;
		if (rdev->ce_fw->size != ce_req_size) {
			pr_err("si_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->ce_fw->size, fw_name);
			err = -EINVAL;
		}
	} else {
		err = radeon_ucode_validate(rdev->ce_fw);
		if (err) {
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_rlc.bin", new_chip_name);
	err = request_firmware(&rdev->rlc_fw, fw_name, rdev->dev);
	if (err) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_rlc.bin", chip_name);
		err = request_firmware(&rdev->rlc_fw, fw_name, rdev->dev);
		if (err)
			goto out;
		if (rdev->rlc_fw->size != rlc_req_size) {
			pr_err("si_rlc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->rlc_fw->size, fw_name);
			err = -EINVAL;
		}
	} else {
		err = radeon_ucode_validate(rdev->rlc_fw);
		if (err) {
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	if (si58_fw)
		snprintf(fw_name, sizeof(fw_name), "radeon/si58_mc.bin");
	else
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_mc.bin", new_chip_name);
	err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
	if (err) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_mc2.bin", chip_name);
		err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
		if (err) {
			snprintf(fw_name, sizeof(fw_name), "radeon/%s_mc.bin", chip_name);
			err = request_firmware(&rdev->mc_fw, fw_name, rdev->dev);
			if (err)
				goto out;
		}
		if ((rdev->mc_fw->size != mc_req_size) &&
		    (rdev->mc_fw->size != mc2_req_size)) {
			pr_err("si_mc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->mc_fw->size, fw_name);
			err = -EINVAL;
		}
		DRM_INFO("%s: %zu bytes\n", fw_name, rdev->mc_fw->size);
	} else {
		err = radeon_ucode_validate(rdev->mc_fw);
		if (err) {
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	if (banks2_fw)
		snprintf(fw_name, sizeof(fw_name), "radeon/banks_k_2_smc.bin");
	else if (new_smc)
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_k_smc.bin", new_chip_name);
	else
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_smc.bin", new_chip_name);
	err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
	if (err) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_smc.bin", chip_name);
		err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
		if (err) {
			pr_err("smc: error loading firmware \"%s\"\n", fw_name);
			release_firmware(rdev->smc_fw);
			rdev->smc_fw = NULL;
			err = 0;
		} else if (rdev->smc_fw->size != smc_req_size) {
			pr_err("si_smc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->smc_fw->size, fw_name);
			err = -EINVAL;
		}
	} else {
		err = radeon_ucode_validate(rdev->smc_fw);
		if (err) {
			pr_err("si_cp: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	if (new_fw == 0) {
		rdev->new_fw = false;
	} else if (new_fw < 6) {
		pr_err("si_fw: mixing new and old firmware!\n");
		err = -EINVAL;
	} else {
		rdev->new_fw = true;
	}
out:
	if (err) {
		if (err != -EINVAL)
			pr_err("si_cp: Failed to load firmware \"%s\"\n",
			       fw_name);
		release_firmware(rdev->pfp_fw);
		rdev->pfp_fw = NULL;
		release_firmware(rdev->me_fw);
		rdev->me_fw = NULL;
		release_firmware(rdev->ce_fw);
		rdev->ce_fw = NULL;
		release_firmware(rdev->rlc_fw);
		rdev->rlc_fw = NULL;
		release_firmware(rdev->mc_fw);
		rdev->mc_fw = NULL;
		release_firmware(rdev->smc_fw);
		rdev->smc_fw = NULL;
	}
	return err;
}