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
struct edgeport_serial {int /*<<< orphan*/  heartbeat_work; int /*<<< orphan*/  use_heartbeat; } ;

/* Variables and functions */
 int FW_HEARTBEAT_SECS ; 
 int HZ ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void edge_heartbeat_schedule(struct edgeport_serial *edge_serial)
{
	if (!edge_serial->use_heartbeat)
		return;

	schedule_delayed_work(&edge_serial->heartbeat_work,
			FW_HEARTBEAT_SECS * HZ);
}