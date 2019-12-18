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

/* Variables and functions */
 unsigned int TICKS_TO_SECS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpwdt_timer_reg ; 
 int /*<<< orphan*/  ioread16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int hpwdt_gettimeleft(struct watchdog_device *wdd)
{
	return TICKS_TO_SECS(ioread16(hpwdt_timer_reg));
}