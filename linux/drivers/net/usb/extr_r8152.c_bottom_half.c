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
struct r8152 {int /*<<< orphan*/  flags; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 int /*<<< orphan*/  SCHEDULE_TASKLET ; 
 int /*<<< orphan*/  WORK_ENABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_bottom (struct r8152*) ; 

__attribute__((used)) static void bottom_half(unsigned long data)
{
	struct r8152 *tp;

	tp = (struct r8152 *)data;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	if (!test_bit(WORK_ENABLE, &tp->flags))
		return;

	/* When link down, the driver would cancel all bulks. */
	/* This avoid the re-submitting bulk */
	if (!netif_carrier_ok(tp->netdev))
		return;

	clear_bit(SCHEDULE_TASKLET, &tp->flags);

	tx_bottom(tp);
}