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
typedef  int uint32_t ;
struct dce_bw_output {int dispclk_khz; int sclk_khz; } ;
struct bw_calcs_vbios {int /*<<< orphan*/  high_sclk; int /*<<< orphan*/  high_voltage_max_dispclk; } ;

/* Variables and functions */
 int bw_fixed_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_display_configuration_supported(
	const struct bw_calcs_vbios *vbios,
	const struct dce_bw_output *calcs_output)
{
	uint32_t int_max_clk;

	int_max_clk = bw_fixed_to_int(vbios->high_voltage_max_dispclk);
	int_max_clk *= 1000; /* MHz to kHz */
	if (calcs_output->dispclk_khz > int_max_clk)
		return false;

	int_max_clk = bw_fixed_to_int(vbios->high_sclk);
	int_max_clk *= 1000; /* MHz to kHz */
	if (calcs_output->sclk_khz > int_max_clk)
		return false;

	return true;
}