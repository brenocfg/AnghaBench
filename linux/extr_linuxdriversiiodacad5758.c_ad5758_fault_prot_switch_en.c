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
struct ad5758_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5758_DCDC_CONFIG1 ; 
 int /*<<< orphan*/  AD5758_DCDC_CONFIG1_PROT_SW_EN_MODE (int) ; 
 int /*<<< orphan*/  AD5758_DCDC_CONFIG1_PROT_SW_EN_MSK ; 
 int /*<<< orphan*/  AD5758_DCDC_CONFIG2 ; 
 int /*<<< orphan*/  AD5758_DCDC_CONFIG2_BUSY_3WI_MSK ; 
 int ad5758_spi_write_mask (struct ad5758_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ad5758_wait_for_task_complete (struct ad5758_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5758_fault_prot_switch_en(struct ad5758_state *st, bool enable)
{
	int ret;

	ret = ad5758_spi_write_mask(st, AD5758_DCDC_CONFIG1,
			AD5758_DCDC_CONFIG1_PROT_SW_EN_MSK,
			AD5758_DCDC_CONFIG1_PROT_SW_EN_MODE(enable));
	if (ret < 0)
		return ret;
	/*
	 * Poll the BUSY_3WI bit in the DCDC_CONFIG2 register until it is 0.
	 * This allows the 3-wire interface communication to complete.
	 */
	return ad5758_wait_for_task_complete(st, AD5758_DCDC_CONFIG2,
					     AD5758_DCDC_CONFIG2_BUSY_3WI_MSK);
}