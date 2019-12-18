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
struct bios_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_dig_encoder_control (struct bios_parser*) ; 
 int /*<<< orphan*/  init_enable_crtc (struct bios_parser*) ; 
 int /*<<< orphan*/  init_enable_disp_power_gating (struct bios_parser*) ; 
 int /*<<< orphan*/  init_external_encoder_control (struct bios_parser*) ; 
 int /*<<< orphan*/  init_get_smu_clock_info (struct bios_parser*) ; 
 int /*<<< orphan*/  init_set_crtc_timing (struct bios_parser*) ; 
 int /*<<< orphan*/  init_set_dce_clock (struct bios_parser*) ; 
 int /*<<< orphan*/  init_set_pixel_clock (struct bios_parser*) ; 
 int /*<<< orphan*/  init_transmitter_control (struct bios_parser*) ; 

void dal_firmware_parser_init_cmd_tbl(struct bios_parser *bp)
{
	init_dig_encoder_control(bp);
	init_transmitter_control(bp);
	init_set_pixel_clock(bp);

	init_set_crtc_timing(bp);

	init_enable_crtc(bp);

	init_external_encoder_control(bp);
	init_enable_disp_power_gating(bp);
	init_set_dce_clock(bp);
	init_get_smu_clock_info(bp);

}