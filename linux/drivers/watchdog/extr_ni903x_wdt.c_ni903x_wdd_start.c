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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct ni903x_wdt {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ NIWD_CONTROL ; 
 int NIWD_CONTROL_PROC_RESET ; 
 int NIWD_CONTROL_RESET ; 
 int /*<<< orphan*/  ni903x_start (struct ni903x_wdt*) ; 
 int /*<<< orphan*/  ni903x_wdd_set_timeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 struct ni903x_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int ni903x_wdd_start(struct watchdog_device *wdd)
{
	struct ni903x_wdt *wdt = watchdog_get_drvdata(wdd);

	outb(NIWD_CONTROL_RESET | NIWD_CONTROL_PROC_RESET,
	     wdt->io_base + NIWD_CONTROL);

	ni903x_wdd_set_timeout(wdd, wdd->timeout);
	ni903x_start(wdt);

	return 0;
}