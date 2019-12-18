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
struct zfcp_adapter {unsigned long next_port_scan; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 unsigned long min (unsigned long,unsigned long) ; 
 unsigned long msecs_to_jiffies (scalar_t__) ; 
 scalar_t__ port_scan_backoff ; 
 scalar_t__ port_scan_ratelimit ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void zfcp_fc_port_scan(struct zfcp_adapter *adapter)
{
	unsigned long now = jiffies;
	unsigned long next = adapter->next_port_scan;
	unsigned long delay = 0, max;

	/* delay only needed within waiting period */
	if (time_before(now, next)) {
		delay = next - now;
		/* paranoia: never ever delay scans longer than specified */
		max = msecs_to_jiffies(port_scan_ratelimit + port_scan_backoff);
		delay = min(delay, max);
	}

	queue_delayed_work(adapter->work_queue, &adapter->scan_work, delay);
}