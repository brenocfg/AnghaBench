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
struct dm_snapshot {int /*<<< orphan*/  state_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUNNING_MERGE ; 
 int /*<<< orphan*/  SHUTDOWN_MERGE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stop_merge(struct dm_snapshot *s)
{
	set_bit(SHUTDOWN_MERGE, &s->state_bits);
	wait_on_bit(&s->state_bits, RUNNING_MERGE, TASK_UNINTERRUPTIBLE);
	clear_bit(SHUTDOWN_MERGE, &s->state_bits);
}