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
struct tape_med_state_work_data {int state; int /*<<< orphan*/  work; int /*<<< orphan*/  device; } ;
struct tape_device {int dummy; } ;
typedef  enum tape_medium_state { ____Placeholder_tape_medium_state } tape_medium_state ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tape_med_state_work_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tape_get_device (struct tape_device*) ; 
 int /*<<< orphan*/  tape_med_state_work_handler ; 

__attribute__((used)) static void
tape_med_state_work(struct tape_device *device, enum tape_medium_state state)
{
	struct tape_med_state_work_data *p;

	p = kzalloc(sizeof(*p), GFP_ATOMIC);
	if (p) {
		INIT_WORK(&p->work, tape_med_state_work_handler);
		p->device = tape_get_device(device);
		p->state = state;
		schedule_work(&p->work);
	}
}