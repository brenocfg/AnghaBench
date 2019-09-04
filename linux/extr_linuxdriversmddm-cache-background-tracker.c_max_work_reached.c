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
struct background_tracker {scalar_t__ max_work; int /*<<< orphan*/  pending_demotes; int /*<<< orphan*/  pending_writebacks; int /*<<< orphan*/  pending_promotes; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool max_work_reached(struct background_tracker *b)
{
	return atomic_read(&b->pending_promotes) +
		atomic_read(&b->pending_writebacks) +
		atomic_read(&b->pending_demotes) >= b->max_work;
}