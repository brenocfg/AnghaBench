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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {int dummy; } ;
typedef  int /*<<< orphan*/  pp_atomctrl_internal_ss_info ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_ENGINE_SS ; 
 int asic_internal_ss_get_ss_asignment (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

int atomctrl_get_engine_clock_spread_spectrum(
		struct pp_hwmgr *hwmgr,
		const uint32_t engine_clock,
		pp_atomctrl_internal_ss_info *ssInfo)
{
	return asic_internal_ss_get_ss_asignment(hwmgr,
			ASIC_INTERNAL_ENGINE_SS, engine_clock, ssInfo);
}