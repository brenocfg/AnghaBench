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
 int /*<<< orphan*/  KEYLARGO_FCR1 ; 
 int /*<<< orphan*/  KEYLARGO_MBCR ; 
 int KL1_EIDE0_ENABLE ; 
 int KL1_EIDE0_RESET_N ; 
 int KL_MBCR_MB0_DEV_MASK ; 
 int KL_MBCR_MB0_DEV_POWER ; 
 int KL_MBCR_MB0_DEV_RESET ; 
 int /*<<< orphan*/  MB_BIC (struct media_bay_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MB_BIS (struct media_bay_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
keylargo_mb_power(struct media_bay_info* bay, int on_off)
{
	if (on_off) {
		/* Power up device, assert it's reset line */
            	MB_BIC(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_RESET);
            	MB_BIC(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_POWER);
	} else {
		/* Disable all devices */
		MB_BIC(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_MASK);
		MB_BIC(bay, KEYLARGO_FCR1, KL1_EIDE0_ENABLE);
		/* Cut power from bay, release reset line */
		MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_POWER);
		MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_RESET);
		MB_BIS(bay, KEYLARGO_FCR1, KL1_EIDE0_RESET_N);
	}
	MB_BIC(bay, KEYLARGO_MBCR, 0x0000000F);
}