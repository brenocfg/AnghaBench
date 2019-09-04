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
struct timer_list {int dummy; } ;
struct infrared {int keypressed; int /*<<< orphan*/  input_dev; int /*<<< orphan*/  last_key; } ;

/* Variables and functions */
 struct infrared* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 struct infrared* ir ; 
 int /*<<< orphan*/  keyup_timer ; 

__attribute__((used)) static void av7110_emit_keyup(struct timer_list *t)
{
	struct infrared *ir = from_timer(ir, t, keyup_timer);

	if (!ir || !ir->keypressed)
		return;

	input_report_key(ir->input_dev, ir->last_key, 0);
	input_sync(ir->input_dev);
	ir->keypressed = false;
}