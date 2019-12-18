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
struct watchdog_device {int max_hw_heartbeat_ms; int /*<<< orphan*/  timeout; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int SECS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hpwdt_timer_con ; 
 int /*<<< orphan*/  hpwdt_timer_reg ; 
 int /*<<< orphan*/  iowrite16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pretimeout ; 

__attribute__((used)) static int hpwdt_start(struct watchdog_device *wdd)
{
	int control = 0x81 | (pretimeout ? 0x4 : 0);
	int reload = SECS_TO_TICKS(min(wdd->timeout, wdd->max_hw_heartbeat_ms/1000));

	dev_dbg(wdd->parent, "start watchdog 0x%08x:0x%08x:0x%02x\n", wdd->timeout, reload, control);
	iowrite16(reload, hpwdt_timer_reg);
	iowrite8(control, hpwdt_timer_con);

	return 0;
}