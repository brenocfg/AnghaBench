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
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_TCR ; 
 int /*<<< orphan*/  WDTP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTP_MASK ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_to_period (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __booke_wdt_set(void *data)
{
	u32 val;
	struct watchdog_device *wdog = data;

	val = mfspr(SPRN_TCR);
	val &= ~WDTP_MASK;
	val |= WDTP(sec_to_period(wdog->timeout));

	mtspr(SPRN_TCR, val);
}