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
struct io_tracker {unsigned long in_flight; unsigned long idle_time; int /*<<< orphan*/  last_update_time; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iot_init(struct io_tracker *iot)
{
	spin_lock_init(&iot->lock);
	iot->in_flight = 0ul;
	iot->idle_time = 0ul;
	iot->last_update_time = jiffies;
}