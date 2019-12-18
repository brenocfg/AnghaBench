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
typedef  int u32 ;
struct intel_soc_dts_sensors {scalar_t__ intr_type; int tj_max; } ;
struct intel_soc_dts_sensor_entry {int* trip_types; struct intel_soc_dts_sensors* sensors; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 scalar_t__ INTEL_SOC_DTS_INTERRUPT_MSI ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  MBI_REG_WRITE ; 
 int SOC_DTS_AUX0_ENABLE_BIT ; 
 int SOC_DTS_AUX1_ENABLE_BIT ; 
 int SOC_DTS_CPU_MODULE0_ENABLE_BIT ; 
 int SOC_DTS_CPU_MODULE1_ENABLE_BIT ; 
 scalar_t__ SOC_DTS_OFFSET_PTMC ; 
 scalar_t__ SOC_DTS_OFFSET_PTPS ; 
 int SOC_DTS_TE_APICA_ENABLE ; 
 scalar_t__ SOC_DTS_TE_AUX0 ; 
 int SOC_DTS_TE_MSI_ENABLE ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int update_trip_temp(struct intel_soc_dts_sensor_entry *dts,
			    int thres_index, int temp,
			    enum thermal_trip_type trip_type)
{
	int status;
	u32 temp_out;
	u32 out;
	u32 store_ptps;
	u32 store_ptmc;
	u32 store_te_out;
	u32 te_out;
	u32 int_enable_bit = SOC_DTS_TE_APICA_ENABLE;
	struct intel_soc_dts_sensors *sensors = dts->sensors;

	if (sensors->intr_type == INTEL_SOC_DTS_INTERRUPT_MSI)
		int_enable_bit |= SOC_DTS_TE_MSI_ENABLE;

	temp_out = (sensors->tj_max - temp) / 1000;

	status = iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_PTPS, &store_ptps);
	if (status)
		return status;

	out = (store_ptps & ~(0xFF << (thres_index * 8)));
	out |= (temp_out & 0xFF) << (thres_index * 8);
	status = iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				SOC_DTS_OFFSET_PTPS, out);
	if (status)
		return status;

	pr_debug("update_trip_temp PTPS = %x\n", out);
	status = iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_PTMC, &out);
	if (status)
		goto err_restore_ptps;

	store_ptmc = out;

	status = iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_TE_AUX0 + thres_index,
			       &te_out);
	if (status)
		goto err_restore_ptmc;

	store_te_out = te_out;
	/* Enable for CPU module 0 and module 1 */
	out |= (SOC_DTS_CPU_MODULE0_ENABLE_BIT |
					SOC_DTS_CPU_MODULE1_ENABLE_BIT);
	if (temp) {
		if (thres_index)
			out |= SOC_DTS_AUX1_ENABLE_BIT;
		else
			out |= SOC_DTS_AUX0_ENABLE_BIT;
		te_out |= int_enable_bit;
	} else {
		if (thres_index)
			out &= ~SOC_DTS_AUX1_ENABLE_BIT;
		else
			out &= ~SOC_DTS_AUX0_ENABLE_BIT;
		te_out &= ~int_enable_bit;
	}
	status = iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				SOC_DTS_OFFSET_PTMC, out);
	if (status)
		goto err_restore_te_out;

	status = iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
				SOC_DTS_TE_AUX0 + thres_index,
				te_out);
	if (status)
		goto err_restore_te_out;

	dts->trip_types[thres_index] = trip_type;

	return 0;
err_restore_te_out:
	iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
		       SOC_DTS_OFFSET_PTMC, store_te_out);
err_restore_ptmc:
	iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
		       SOC_DTS_OFFSET_PTMC, store_ptmc);
err_restore_ptps:
	iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
		       SOC_DTS_OFFSET_PTPS, store_ptps);
	/* Nothing we can do if restore fails */

	return status;
}