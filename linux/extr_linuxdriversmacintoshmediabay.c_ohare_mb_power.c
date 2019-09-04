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
 int /*<<< orphan*/  MB_BIC (struct media_bay_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MB_BIS (struct media_bay_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OHARE_FCR ; 
 int /*<<< orphan*/  OHARE_MBCR ; 
 int OH_BAY_DEV_MASK ; 
 int OH_BAY_POWER_N ; 
 int OH_BAY_RESET_N ; 
 int OH_FLOPPY_ENABLE ; 
 int OH_IDE1_RESET_N ; 

__attribute__((used)) static void
ohare_mb_power(struct media_bay_info* bay, int on_off)
{
	if (on_off) {
		/* Power up device, assert it's reset line */
		MB_BIC(bay, OHARE_FCR, OH_BAY_RESET_N);
		MB_BIC(bay, OHARE_FCR, OH_BAY_POWER_N);
	} else {
		/* Disable all devices */
		MB_BIC(bay, OHARE_FCR, OH_BAY_DEV_MASK);
		MB_BIC(bay, OHARE_FCR, OH_FLOPPY_ENABLE);
		/* Cut power from bay, release reset line */
		MB_BIS(bay, OHARE_FCR, OH_BAY_POWER_N);
		MB_BIS(bay, OHARE_FCR, OH_BAY_RESET_N);
		MB_BIS(bay, OHARE_FCR, OH_IDE1_RESET_N);
	}
	MB_BIC(bay, OHARE_MBCR, 0x00000F00);
}