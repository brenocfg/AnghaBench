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
struct watchdog_device {int dummy; } ;
struct tqmx86_wdt {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ TQMX86_WDCS ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 struct tqmx86_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int tqmx86_wdt_start(struct watchdog_device *wdd)
{
	struct tqmx86_wdt *priv = watchdog_get_drvdata(wdd);

	iowrite8(0x81, priv->io_base + TQMX86_WDCS);

	return 0;
}