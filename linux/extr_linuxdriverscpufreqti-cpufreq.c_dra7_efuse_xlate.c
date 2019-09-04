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
struct ti_cpufreq_data {int dummy; } ;

/* Variables and functions */
#define  DRA7_EFUSE_HAS_ALL_MPU_OPP 130 
#define  DRA7_EFUSE_HAS_HIGH_MPU_OPP 129 
#define  DRA7_EFUSE_HAS_OD_MPU_OPP 128 
 unsigned long DRA7_EFUSE_HIGH_MPU_OPP ; 
 unsigned long DRA7_EFUSE_NOM_MPU_OPP ; 
 unsigned long DRA7_EFUSE_OD_MPU_OPP ; 

__attribute__((used)) static unsigned long dra7_efuse_xlate(struct ti_cpufreq_data *opp_data,
				      unsigned long efuse)
{
	unsigned long calculated_efuse = DRA7_EFUSE_NOM_MPU_OPP;

	/*
	 * The efuse on dra7 and am57 parts contains a specific
	 * value indicating the highest available OPP.
	 */

	switch (efuse) {
	case DRA7_EFUSE_HAS_ALL_MPU_OPP:
	case DRA7_EFUSE_HAS_HIGH_MPU_OPP:
		calculated_efuse |= DRA7_EFUSE_HIGH_MPU_OPP;
	case DRA7_EFUSE_HAS_OD_MPU_OPP:
		calculated_efuse |= DRA7_EFUSE_OD_MPU_OPP;
	}

	return calculated_efuse;
}