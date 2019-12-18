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
typedef  int u32 ;
struct watchdog_device {unsigned int timeout; } ;
struct ni903x_wdt {scalar_t__ io_base; } ;

/* Variables and functions */
 int NIWD_PERIOD_NS ; 
 scalar_t__ NIWD_SEED0 ; 
 scalar_t__ NIWD_SEED1 ; 
 scalar_t__ NIWD_SEED2 ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 struct ni903x_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int ni903x_wdd_set_timeout(struct watchdog_device *wdd,
				  unsigned int timeout)
{
	struct ni903x_wdt *wdt = watchdog_get_drvdata(wdd);
	u32 counter = timeout * (1000000000 / NIWD_PERIOD_NS);

	outb(((0x00FF0000 & counter) >> 16), wdt->io_base + NIWD_SEED2);
	outb(((0x0000FF00 & counter) >> 8), wdt->io_base + NIWD_SEED1);
	outb((0x000000FF & counter), wdt->io_base + NIWD_SEED0);

	wdd->timeout = timeout;

	return 0;
}