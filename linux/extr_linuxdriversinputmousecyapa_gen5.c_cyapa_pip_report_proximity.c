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
typedef  int u8 ;
struct input_dev {int dummy; } ;
struct cyapa_pip_report_data {int* report_head; } ;
struct cyapa {struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int PIP_PROXIMITY_DISTANCE_MASK ; 
 size_t PIP_PROXIMITY_DISTANCE_OFFSET ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void cyapa_pip_report_proximity(struct cyapa *cyapa,
		const struct cyapa_pip_report_data *report_data)
{
	struct input_dev *input = cyapa->input;
	u8 distance = report_data->report_head[PIP_PROXIMITY_DISTANCE_OFFSET] &
			PIP_PROXIMITY_DISTANCE_MASK;

	input_report_abs(input, ABS_DISTANCE, distance);
	input_sync(input);
}