#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  crystal_frequency; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct dc_firmware_info {TYPE_3__ pll_info; TYPE_1__ member_0; } ;
struct dc_bios {TYPE_2__* funcs; } ;
struct TYPE_5__ {scalar_t__ (* get_firmware_info ) (struct dc_bios*,struct dc_firmware_info*) ;} ;

/* Variables and functions */
 scalar_t__ BP_RESULT_OK ; 
 scalar_t__ stub1 (struct dc_bios*,struct dc_firmware_info*) ; 

uint32_t dal_i2caux_get_reference_clock(
		struct dc_bios *bios)
{
	struct dc_firmware_info info = { { 0 } };

	if (bios->funcs->get_firmware_info(bios, &info) != BP_RESULT_OK)
		return 0;

	return info.pll_info.crystal_frequency;
}