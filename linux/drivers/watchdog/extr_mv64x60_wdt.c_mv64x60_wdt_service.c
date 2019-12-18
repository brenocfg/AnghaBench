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
 int /*<<< orphan*/  MV64x60_WDC_ENABLED_TRUE ; 
 int /*<<< orphan*/  MV64x60_WDC_SERVICE_SHIFT ; 
 int /*<<< orphan*/  mv64x60_wdt_toggle_wdc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv64x60_wdt_service(void)
{
	mv64x60_wdt_toggle_wdc(MV64x60_WDC_ENABLED_TRUE,
			       MV64x60_WDC_SERVICE_SHIFT);
}