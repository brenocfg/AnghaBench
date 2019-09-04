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

/* Variables and functions */
 int /*<<< orphan*/  OMAP24XX_VA_READPERM0 ; 
 int /*<<< orphan*/  OMAP24XX_VA_REQINFOPERM0 ; 
 int /*<<< orphan*/  OMAP24XX_VA_WRITEPERM0 ; 
 scalar_t__ OMAP2_DEVICE_TYPE_GP ; 
 int /*<<< orphan*/  OMAP34XX_VA_ADDR_MATCH2 ; 
 int /*<<< orphan*/  OMAP34XX_VA_READPERM0 ; 
 int /*<<< orphan*/  OMAP34XX_VA_REQINFOPERM0 ; 
 int /*<<< orphan*/  OMAP34XX_VA_SMS_RG_ATT0 ; 
 int /*<<< orphan*/  OMAP34XX_VA_WRITEPERM0 ; 
 scalar_t__ cpu_is_omap242x () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 scalar_t__ omap_type () ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_sram_locked(void)
{
	if (OMAP2_DEVICE_TYPE_GP == omap_type()) {
		/* RAMFW: R/W access to all initiators for all qualifier sets */
		if (cpu_is_omap242x()) {
			writel_relaxed(0xFF, OMAP24XX_VA_REQINFOPERM0); /* all q-vects */
			writel_relaxed(0xCFDE, OMAP24XX_VA_READPERM0);  /* all i-read */
			writel_relaxed(0xCFDE, OMAP24XX_VA_WRITEPERM0); /* all i-write */
		}
		if (cpu_is_omap34xx()) {
			writel_relaxed(0xFFFF, OMAP34XX_VA_REQINFOPERM0); /* all q-vects */
			writel_relaxed(0xFFFF, OMAP34XX_VA_READPERM0);  /* all i-read */
			writel_relaxed(0xFFFF, OMAP34XX_VA_WRITEPERM0); /* all i-write */
			writel_relaxed(0x0, OMAP34XX_VA_ADDR_MATCH2);
			writel_relaxed(0xFFFFFFFF, OMAP34XX_VA_SMS_RG_ATT0);
		}
		return 0;
	} else
		return 1; /* assume locked with no PPA or security driver */
}