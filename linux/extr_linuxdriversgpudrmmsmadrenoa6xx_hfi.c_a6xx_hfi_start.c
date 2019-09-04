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
struct a6xx_gmu {int dummy; } ;

/* Variables and functions */
 int a6xx_hfi_get_fw_version (struct a6xx_gmu*,int /*<<< orphan*/ *) ; 
 int a6xx_hfi_send_bw_table (struct a6xx_gmu*) ; 
 int a6xx_hfi_send_gmu_init (struct a6xx_gmu*,int) ; 
 int a6xx_hfi_send_perf_table (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_hfi_send_test (struct a6xx_gmu*) ; 

int a6xx_hfi_start(struct a6xx_gmu *gmu, int boot_state)
{
	int ret;

	ret = a6xx_hfi_send_gmu_init(gmu, boot_state);
	if (ret)
		return ret;

	ret = a6xx_hfi_get_fw_version(gmu, NULL);
	if (ret)
		return ret;

	/*
	 * We have to get exchange version numbers per the sequence but at this
	 * point th kernel driver doesn't need to know the exact version of
	 * the GMU firmware
	 */

	ret = a6xx_hfi_send_perf_table(gmu);
	if (ret)
		return ret;

	ret = a6xx_hfi_send_bw_table(gmu);
	if (ret)
		return ret;

	/*
	 * Let the GMU know that there won't be any more HFI messages until next
	 * boot
	 */
	a6xx_hfi_send_test(gmu);

	return 0;
}