#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timing_generator {TYPE_1__* funcs; } ;
struct crtc_position {scalar_t__ horizontal_count; scalar_t__ vertical_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_position ) (struct timing_generator*,struct crtc_position*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct timing_generator*,struct crtc_position*) ; 
 int /*<<< orphan*/  stub2 (struct timing_generator*,struct crtc_position*) ; 

bool optc1_is_counter_moving(struct timing_generator *optc)
{
	struct crtc_position position1, position2;

	optc->funcs->get_position(optc, &position1);
	optc->funcs->get_position(optc, &position2);

	if (position1.horizontal_count == position2.horizontal_count &&
		position1.vertical_count == position2.vertical_count)
		return false;
	else
		return true;
}