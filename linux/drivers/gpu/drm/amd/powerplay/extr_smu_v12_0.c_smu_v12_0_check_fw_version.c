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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct smu_context {int smc_if_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int smu_get_smc_version (struct smu_context*,int*,int*) ; 

__attribute__((used)) static int smu_v12_0_check_fw_version(struct smu_context *smu)
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