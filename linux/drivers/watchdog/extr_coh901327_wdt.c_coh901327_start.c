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
struct watchdog_device {int timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  coh901327_enable (int) ; 

__attribute__((used)) static int coh901327_start(struct watchdog_device *wdt_dev)
{
	coh901327_enable(wdt_dev->timeout * 100);
	return 0;
}