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
struct input_polled_dev {int /*<<< orphan*/  poll_interval; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  POLL_INTERVAL_BURST ; 
 int /*<<< orphan*/  POLL_INTERVAL_DEFAULT ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ jiffies_last_press ; 
 int /*<<< orphan*/  poll_bios (int) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void wistron_poll(struct input_polled_dev *dev)
{
	poll_bios(false);

	/* Increase poll frequency if user is currently pressing keys (< 2s ago) */
	if (time_before(jiffies, jiffies_last_press + 2 * HZ))
		dev->poll_interval = POLL_INTERVAL_BURST;
	else
		dev->poll_interval = POLL_INTERVAL_DEFAULT;
}