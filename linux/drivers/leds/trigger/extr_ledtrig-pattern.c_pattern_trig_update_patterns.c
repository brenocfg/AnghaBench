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
struct pattern_trig_data {int curr; int next; int patterns; int npatterns; scalar_t__ delta_t; int /*<<< orphan*/  repeat; int /*<<< orphan*/  is_indefinite; } ;

/* Variables and functions */

__attribute__((used)) static void pattern_trig_update_patterns(struct pattern_trig_data *data)
{
	data->curr = data->next;
	if (!data->is_indefinite && data->curr == data->patterns)
		data->repeat--;

	if (data->next == data->patterns + data->npatterns - 1)
		data->next = data->patterns;
	else
		data->next++;

	data->delta_t = 0;
}