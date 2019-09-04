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
struct dm_target {struct delay_c* private; } ;
struct delay_c {int /*<<< orphan*/  delay_timer; int /*<<< orphan*/  may_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_bios (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_delayed_bios (struct delay_c*,int) ; 

__attribute__((used)) static void delay_presuspend(struct dm_target *ti)
{
	struct delay_c *dc = ti->private;

	atomic_set(&dc->may_delay, 0);
	del_timer_sync(&dc->delay_timer);
	flush_bios(flush_delayed_bios(dc, 1));
}