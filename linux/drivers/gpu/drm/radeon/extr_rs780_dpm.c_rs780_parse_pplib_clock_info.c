#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ucLowEngineClockHigh; int ucHighEngineClockHigh; int /*<<< orphan*/  ulFlags; int /*<<< orphan*/  usVDDC; int /*<<< orphan*/  usHighEngineClockLow; int /*<<< orphan*/  usLowEngineClockLow; } ;
union pplib_clock_info {TYPE_1__ rs780; } ;
typedef  int u32 ;
struct radeon_ps {int class; } ;
struct TYPE_4__ {int default_sclk; } ;
struct radeon_device {TYPE_2__ clock; } ;
struct igp_ps {int sclk_low; int sclk_high; void* max_voltage; void* min_voltage; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION_BOOT ; 
#define  ATOM_PPLIB_RS780_VOLTAGE_HIGH 131 
#define  ATOM_PPLIB_RS780_VOLTAGE_LOW 130 
#define  ATOM_PPLIB_RS780_VOLTAGE_NONE 129 
#define  ATOM_PPLIB_RS780_VOLTAGE_VARIABLE 128 
 void* RS780_VDDC_LEVEL_HIGH ; 
 void* RS780_VDDC_LEVEL_LOW ; 
 void* RS780_VDDC_LEVEL_UNKNOWN ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct igp_ps* rs780_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void rs780_parse_pplib_clock_info(struct radeon_device *rdev,
					 struct radeon_ps *rps,
					 union pplib_clock_info *clock_info)
{
	struct igp_ps *ps = rs780_get_ps(rps);
	u32 sclk;

	sclk = le16_to_cpu(clock_info->rs780.usLowEngineClockLow);
	sclk |= clock_info->rs780.ucLowEngineClockHigh << 16;
	ps->sclk_low = sclk;
	sclk = le16_to_cpu(clock_info->rs780.usHighEngineClockLow);
	sclk |= clock_info->rs780.ucHighEngineClockHigh << 16;
	ps->sclk_high = sclk;
	switch (le16_to_cpu(clock_info->rs780.usVDDC)) {
	case ATOM_PPLIB_RS780_VOLTAGE_NONE:
	default:
		ps->min_voltage = RS780_VDDC_LEVEL_UNKNOWN;
		ps->max_voltage = RS780_VDDC_LEVEL_UNKNOWN;
		break;
	case ATOM_PPLIB_RS780_VOLTAGE_LOW:
		ps->min_voltage = RS780_VDDC_LEVEL_LOW;
		ps->max_voltage = RS780_VDDC_LEVEL_LOW;
		break;
	case ATOM_PPLIB_RS780_VOLTAGE_HIGH:
		ps->min_voltage = RS780_VDDC_LEVEL_HIGH;
		ps->max_voltage = RS780_VDDC_LEVEL_HIGH;
		break;
	case ATOM_PPLIB_RS780_VOLTAGE_VARIABLE:
		ps->min_voltage = RS780_VDDC_LEVEL_LOW;
		ps->max_voltage = RS780_VDDC_LEVEL_HIGH;
		break;
	}
	ps->flags = le32_to_cpu(clock_info->rs780.ulFlags);

	if (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT) {
		ps->sclk_low = rdev->clock.default_sclk;
		ps->sclk_high = rdev->clock.default_sclk;
		ps->min_voltage = RS780_VDDC_LEVEL_HIGH;
		ps->max_voltage = RS780_VDDC_LEVEL_HIGH;
	}
}