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
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hpwdt_ping_ticks (int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hpwdt_ping(struct watchdog_device *wdd)
{
	int reload = SECS_TO_TICKS(min(wdd->timeout, wdd->max_hw_heartbeat_ms/1000));

	dev_dbg(wdd->parent, "ping  watchdog 0x%08x:0x%08x\n", wdd->timeout, reload);
	hpwdt_ping_ticks(reload);

	return 0;
}