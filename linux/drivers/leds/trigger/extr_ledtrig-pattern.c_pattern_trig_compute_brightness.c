#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pattern_trig_data {int delta_t; TYPE_2__* curr; TYPE_1__* next; } ;
struct TYPE_4__ {int delta_t; int brightness; } ;
struct TYPE_3__ {scalar_t__ brightness; } ;

/* Variables and functions */
 int UPDATE_INTERVAL ; 
 int abs (scalar_t__) ; 

__attribute__((used)) static int pattern_trig_compute_brightness(struct pattern_trig_data *data)
{
	int step_brightness;

	/*
	 * If current tuple's duration is less than the dimming interval,
	 * we should treat it as a step change of brightness instead of
	 * doing gradual dimming.
	 */
	if (data->delta_t == 0 || data->curr->delta_t < UPDATE_INTERVAL)
		return data->curr->brightness;

	step_brightness = abs(data->next->brightness - data->curr->brightness);
	step_brightness = data->delta_t * step_brightness / data->curr->delta_t;

	if (data->next->brightness > data->curr->brightness)
		return data->curr->brightness + step_brightness;
	else
		return data->curr->brightness - step_brightness;
}