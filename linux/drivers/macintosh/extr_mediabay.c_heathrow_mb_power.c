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
struct media_bay_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEATHROW_FCR ; 
 int /*<<< orphan*/  HEATHROW_MBCR ; 
 int HRW_BAY_DEV_MASK ; 
 int HRW_BAY_POWER_N ; 
 int HRW_BAY_RESET_N ; 
 int HRW_IDE1_RESET_N ; 
 int HRW_SWIM_ENABLE ; 
 int /*<<< orphan*/  MB_BIC (struct media_bay_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MB_BIS (struct media_bay_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
heathrow_mb_power(struct media_bay_info* bay, int on_off)
{
	if (on_off) {
		/* Power up device, assert it's reset line */
		MB_BIC(bay, HEATHROW_FCR, HRW_BAY_RESET_N);
		MB_BIC(bay, HEATHROW_FCR, HRW_BAY_POWER_N);
	} else {
		/* Disable all devices */
		MB_BIC(bay, HEATHROW_FCR, HRW_BAY_DEV_MASK);
		MB_BIC(bay, HEATHROW_FCR, HRW_SWIM_ENABLE);
		/* Cut power from bay, release reset line */
		MB_BIS(bay, HEATHROW_FCR, HRW_BAY_POWER_N);
		MB_BIS(bay, HEATHROW_FCR, HRW_BAY_RESET_N);
		MB_BIS(bay, HEATHROW_FCR, HRW_IDE1_RESET_N);
	}
	MB_BIC(bay, HEATHROW_MBCR, 0x00000F00);
}