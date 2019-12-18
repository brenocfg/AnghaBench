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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct smu_context {int smc_if_version; TYPE_1__* adev; } ;
struct TYPE_2__ {int asic_type; } ;

/* Variables and functions */
#define  CHIP_ARCTURUS 131 
#define  CHIP_NAVI10 130 
#define  CHIP_NAVI14 129 
#define  CHIP_VEGA20 128 
 int SMU11_DRIVER_IF_VERSION_ARCT ; 
 int SMU11_DRIVER_IF_VERSION_INV ; 
 int SMU11_DRIVER_IF_VERSION_NV10 ; 
 int SMU11_DRIVER_IF_VERSION_NV14 ; 
 int SMU11_DRIVER_IF_VERSION_VG20 ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int smu_get_smc_version (struct smu_context*,int*,int*) ; 

__attribute__((used)) static int smu_v11_0_check_fw_version(struct smu_context *smu)
{
	uint32_t if_version = 0xff, smu_version = 0xff;
	uint16_t smu_major;
	uint8_t smu_minor, smu_debug;
	int ret = 0;

	ret = smu_get_smc_version(smu, &if_version, &smu_version);
	if (ret)
		return ret;

	smu_major = (smu_version >> 16) & 0xffff;
	smu_minor = (smu_version >> 8) & 0xff;
	smu_debug = (smu_version >> 0) & 0xff;

	switch (smu->adev->asic_type) {
	case CHIP_VEGA20:
		smu->smc_if_version = SMU11_DRIVER_IF_VERSION_VG20;
		break;
	case CHIP_ARCTURUS:
		smu->smc_if_version = SMU11_DRIVER_IF_VERSION_ARCT;
		break;
	case CHIP_NAVI10:
		smu->smc_if_version = SMU11_DRIVER_IF_VERSION_NV10;
		break;
	case CHIP_NAVI14:
		smu->smc_if_version = SMU11_DRIVER_IF_VERSION_NV14;
		break;
	default:
		pr_err("smu unsupported asic type:%d.\n", smu->adev->asic_type);
		smu->smc_if_version = SMU11_DRIVER_IF_VERSION_INV;
		break;
	}

	/*
	 * 1. if_version mismatch is not critical as our fw is designed
	 * to be backward compatible.
	 * 2. New fw usually brings some optimizations. But that's visible
	 * only on the paired driver.
	 * Considering above, we just leave user a warning message instead
	 * of halt driver loading.
	 */
	if (if_version != smu->smc_if_version) {
		pr_info("smu driver if version = 0x%08x, smu fw if version = 0x%08x, "
			"smu fw version = 0x%08x (%d.%d.%d)\n",
			smu->smc_if_version, if_version,
			smu_version, smu_major, smu_minor, smu_debug);
		pr_warn("SMU driver if version not matched\n");
	}

	return ret;
}