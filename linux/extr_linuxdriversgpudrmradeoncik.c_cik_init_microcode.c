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
struct radeon_device {int family; int flags; int new_fw; TYPE_2__* smc_fw; TYPE_2__* mc_fw; TYPE_2__* sdma_fw; TYPE_2__* rlc_fw; TYPE_2__* mec2_fw; TYPE_2__* mec_fw; TYPE_2__* ce_fw; TYPE_2__* me_fw; TYPE_2__* pfp_fw; int /*<<< orphan*/  dev; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  fw_name ;
struct TYPE_6__ {size_t size; } ;
struct TYPE_5__ {int revision; int device; } ;

/* Variables and functions */
 size_t ALIGN (int /*<<< orphan*/ ,int) ; 
 int BONAIRE_MC2_UCODE_SIZE ; 
 int BONAIRE_MC_UCODE_SIZE ; 
 int BONAIRE_RLC_UCODE_SIZE ; 
 int /*<<< orphan*/  BONAIRE_SMC_UCODE_SIZE ; 
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_BONAIRE 132 
#define  CHIP_HAWAII 131 
#define  CHIP_KABINI 130 
#define  CHIP_KAVERI 129 
#define  CHIP_MULLINS 128 
 int CIK_CE_UCODE_SIZE ; 
 int CIK_MEC_UCODE_SIZE ; 
 int CIK_ME_UCODE_SIZE ; 
 int CIK_PFP_UCODE_SIZE ; 
 int CIK_SDMA_UCODE_SIZE ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,char const*,...) ; 
 int EINVAL ; 
 int HAWAII_MC2_UCODE_SIZE ; 
 int HAWAII_MC_UCODE_SIZE ; 
 int /*<<< orphan*/  HAWAII_SMC_UCODE_SIZE ; 
 int KB_RLC_UCODE_SIZE ; 
 int KV_RLC_UCODE_SIZE ; 
 int ML_RLC_UCODE_SIZE ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int radeon_ucode_validate (TYPE_2__*) ; 
 int /*<<< orphan*/  release_firmware (TYPE_2__*) ; 
 int request_firmware (TYPE_2__**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int cik_init_microcode(struct radeon_device *rdev)
{
	const char *chip_name;
	const char *new_chip_name;
	size_t pfp_req_size, me_req_size, ce_req_size,
		mec_req_size, rlc_req_size, mc_req_size = 0,
		sdma_req_size, smc_req_size = 0, mc2_req_size = 0;
	char fw_name[30];
	int new_fw = 0;
	int err;
	int num_fw;
	bool new_smc = false;

	DRM_DEBUG("\n");

	switch (rdev->family) {
	case CHIP_BONAIRE:
		chip_name = "BONAIRE";
		if ((rdev->pdev->revision == 0x80) ||
		    (rdev->pdev->revision == 0x81) ||
		    (rdev->pdev->device == 0x665f))
			new_smc = true;
		new_chip_name = "bonaire";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = BONAIRE_RLC_UCODE_SIZE * 4;
		mc_req_size = BONAIRE_MC_UCODE_SIZE * 4;
		mc2_req_size = BONAIRE_MC2_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		smc_req_size = ALIGN(BONAIRE_SMC_UCODE_SIZE, 4);
		num_fw = 8;
		break;
	case CHIP_HAWAII:
		chip_name = "HAWAII";
		if (rdev->pdev->revision == 0x80)
			new_smc = true;
		new_chip_name = "hawaii";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = BONAIRE_RLC_UCODE_SIZE * 4;
		mc_req_size = HAWAII_MC_UCODE_SIZE * 4;
		mc2_req_size = HAWAII_MC2_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		smc_req_size = ALIGN(HAWAII_SMC_UCODE_SIZE, 4);
		num_fw = 8;
		break;
	case CHIP_KAVERI:
		chip_name = "KAVERI";
		new_chip_name = "kaveri";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = KV_RLC_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		num_fw = 7;
		break;
	case CHIP_KABINI:
		chip_name = "KABINI";
		new_chip_name = "kabini";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = KB_RLC_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		num_fw = 6;
		break;
	case CHIP_MULLINS:
		chip_name = "MULLINS";
		new_chip_name = "mullins";
		pfp_req_size = CIK_PFP_UCODE_SIZE * 4;
		me_req_size = CIK_ME_UCODE_SIZE * 4;
		ce_req_size = CIK_CE_UCODE_SIZE * 4;
		mec_req_size = CIK_MEC_UCODE_SIZE * 4;
		rlc_req_size = ML_RLC_UCODE_SIZE * 4;
		sdma_req_size = CIK_SDMA_UCODE_SIZE * 4;
		num_fw = 6;
		break;
	default: BUG();
	}

	DRM_INFO("Loading %s Microcode\n", new_chip_name);

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_pfp.bin", new_chip_name);
	err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
	if (err) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_pfp.bin", chip_name);
		err = request_firmware(&rdev->pfp_fw, fw_name, rdev->dev);
		if (err)
			goto out;
		if (rdev->pfp_fw->size != pfp_req_size) {
			pr_err("cik_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->pfp_fw->size, fw_name);
			err = -EINVAL;
			goto out;
		}
	} else {
		err = radeon_ucode_validate(rdev->pfp_fw);
		if (err) {
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
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
			pr_err("cik_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->me_fw->size, fw_name);
			err = -EINVAL;
		}
	} else {
		err = radeon_ucode_validate(rdev->me_fw);
		if (err) {
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
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
			pr_err("cik_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->ce_fw->size, fw_name);
			err = -EINVAL;
		}
	} else {
		err = radeon_ucode_validate(rdev->ce_fw);
		if (err) {
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_mec.bin", new_chip_name);
	err = request_firmware(&rdev->mec_fw, fw_name, rdev->dev);
	if (err) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_mec.bin", chip_name);
		err = request_firmware(&rdev->mec_fw, fw_name, rdev->dev);
		if (err)
			goto out;
		if (rdev->mec_fw->size != mec_req_size) {
			pr_err("cik_cp: Bogus length %zu in firmware \"%s\"\n",
			       rdev->mec_fw->size, fw_name);
			err = -EINVAL;
		}
	} else {
		err = radeon_ucode_validate(rdev->mec_fw);
		if (err) {
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	if (rdev->family == CHIP_KAVERI) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_mec2.bin", new_chip_name);
		err = request_firmware(&rdev->mec2_fw, fw_name, rdev->dev);
		if (err) {
			goto out;
		} else {
			err = radeon_ucode_validate(rdev->mec2_fw);
			if (err) {
				goto out;
			} else {
				new_fw++;
			}
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
			pr_err("cik_rlc: Bogus length %zu in firmware \"%s\"\n",
			       rdev->rlc_fw->size, fw_name);
			err = -EINVAL;
		}
	} else {
		err = radeon_ucode_validate(rdev->rlc_fw);
		if (err) {
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	snprintf(fw_name, sizeof(fw_name), "radeon/%s_sdma.bin", new_chip_name);
	err = request_firmware(&rdev->sdma_fw, fw_name, rdev->dev);
	if (err) {
		snprintf(fw_name, sizeof(fw_name), "radeon/%s_sdma.bin", chip_name);
		err = request_firmware(&rdev->sdma_fw, fw_name, rdev->dev);
		if (err)
			goto out;
		if (rdev->sdma_fw->size != sdma_req_size) {
			pr_err("cik_sdma: Bogus length %zu in firmware \"%s\"\n",
			       rdev->sdma_fw->size, fw_name);
			err = -EINVAL;
		}
	} else {
		err = radeon_ucode_validate(rdev->sdma_fw);
		if (err) {
			pr_err("cik_fw: validation failed for firmware \"%s\"\n",
			       fw_name);
			goto out;
		} else {
			new_fw++;
		}
	}

	/* No SMC, MC ucode on APUs */
	if (!(rdev->flags & RADEON_IS_IGP)) {
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
			    (rdev->mc_fw->size != mc2_req_size)){
				pr_err("cik_mc: Bogus length %zu in firmware \"%s\"\n",
				       rdev->mc_fw->size, fw_name);
				err = -EINVAL;
			}
			DRM_INFO("%s: %zu bytes\n", fw_name, rdev->mc_fw->size);
		} else {
			err = radeon_ucode_validate(rdev->mc_fw);
			if (err) {
				pr_err("cik_fw: validation failed for firmware \"%s\"\n",
				       fw_name);
				goto out;
			} else {
				new_fw++;
			}
		}

		if (new_smc)
			snprintf(fw_name, sizeof(fw_name), "radeon/%s_k_smc.bin", new_chip_name);
		else
			snprintf(fw_name, sizeof(fw_name), "radeon/%s_smc.bin", new_chip_name);
		err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
		if (err) {
			snprintf(fw_name, sizeof(fw_name), "radeon/%s_smc.bin", chip_name);
			err = request_firmware(&rdev->smc_fw, fw_name, rdev->dev);
			if (err) {
				pr_err("smc: error loading firmware \"%s\"\n",
				       fw_name);
				release_firmware(rdev->smc_fw);
				rdev->smc_fw = NULL;
				err = 0;
			} else if (rdev->smc_fw->size != smc_req_size) {
				pr_err("cik_smc: Bogus length %zu in firmware \"%s\"\n",
				       rdev->smc_fw->size, fw_name);
				err = -EINVAL;
			}
		} else {
			err = radeon_ucode_validate(rdev->smc_fw);
			if (err) {
				pr_err("cik_fw: validation failed for firmware \"%s\"\n",
				       fw_name);
				goto out;
			} else {
				new_fw++;
			}
		}
	}

	if (new_fw == 0) {
		rdev->new_fw = false;
	} else if (new_fw < num_fw) {
		pr_err("ci_fw: mixing new and old firmware!\n");
		err = -EINVAL;
	} else {
		rdev->new_fw = true;
	}

out:
	if (err) {
		if (err != -EINVAL)
			pr_err("cik_cp: Failed to load firmware \"%s\"\n",
			       fw_name);
		release_firmware(rdev->pfp_fw);
		rdev->pfp_fw = NULL;
		release_firmware(rdev->me_fw);
		rdev->me_fw = NULL;
		release_firmware(rdev->ce_fw);
		rdev->ce_fw = NULL;
		release_firmware(rdev->mec_fw);
		rdev->mec_fw = NULL;
		release_firmware(rdev->mec2_fw);
		rdev->mec2_fw = NULL;
		release_firmware(rdev->rlc_fw);
		rdev->rlc_fw = NULL;
		release_firmware(rdev->sdma_fw);
		rdev->sdma_fw = NULL;
		release_firmware(rdev->mc_fw);
		rdev->mc_fw = NULL;
		release_firmware(rdev->smc_fw);
		rdev->smc_fw = NULL;
	}
	return err;
}