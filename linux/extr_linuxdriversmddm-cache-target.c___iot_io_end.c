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
struct io_tracker {int /*<<< orphan*/  idle_time; scalar_t__ in_flight; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void __iot_io_end(struct io_tracker *iot, sector_t len)
{
	if (!len)
		return;

	iot->in_flight -= len;
	if (!iot->in_flight)
		iot->idle_time = jiffies;
}