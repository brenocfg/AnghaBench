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
struct bcm_kona_wdt {int resolution; } ;

/* Variables and functions */
 int EINVAL ; 
 int SECWDOG_CLKS_SHIFT ; 
 int SECWDOG_MAX_RES ; 
 int /*<<< orphan*/  SECWDOG_RES_MASK ; 
 int bcm_kona_wdt_ctrl_reg_modify (struct bcm_kona_wdt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm_kona_wdt_set_resolution_reg(struct bcm_kona_wdt *wdt)
{
	if (wdt->resolution > SECWDOG_MAX_RES)
		return -EINVAL;

	return bcm_kona_wdt_ctrl_reg_modify(wdt, SECWDOG_RES_MASK,
					wdt->resolution << SECWDOG_CLKS_SHIFT);
}