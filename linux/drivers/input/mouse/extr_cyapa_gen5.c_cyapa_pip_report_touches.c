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
struct input_dev {int dummy; } ;
struct cyapa_pip_report_data {unsigned int* report_head; int /*<<< orphan*/ * touch_records; } ;
struct cyapa {struct input_dev* input; } ;

/* Variables and functions */
 unsigned int PIP_NUMBER_OF_TOUCH_MASK ; 
 size_t PIP_NUMBER_OF_TOUCH_OFFSET ; 
 int /*<<< orphan*/  cyapa_pip_report_slot_data (struct cyapa*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_mt_sync_frame (struct input_dev*) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void cyapa_pip_report_touches(struct cyapa *cyapa,
		const struct cyapa_pip_report_data *report_data)
{
	struct input_dev *input = cyapa->input;
	unsigned int touch_num;
	int i;

	touch_num = report_data->report_head[PIP_NUMBER_OF_TOUCH_OFFSET] &
			PIP_NUMBER_OF_TOUCH_MASK;

	for (i = 0; i < touch_num; i++)
		cyapa_pip_report_slot_data(cyapa,
			&report_data->touch_records[i]);

	input_mt_sync_frame(input);
	input_sync(input);
}