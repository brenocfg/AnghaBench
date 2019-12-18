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
struct TYPE_4__ {int /*<<< orphan*/  io_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  wtc; } ;

/* Variables and functions */
 int RC32434_WTC_EN ; 
 int /*<<< orphan*/  SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 TYPE_2__ rc32434_wdt_device ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* wdt_reg ; 

__attribute__((used)) static void rc32434_wdt_stop(void)
{
	spin_lock(&rc32434_wdt_device.io_lock);

	/* Disable WDT */
	SET_BITS(wdt_reg->wtc, 0, 1 << RC32434_WTC_EN);

	spin_unlock(&rc32434_wdt_device.io_lock);
	pr_info("Stopped watchdog timer\n");
}