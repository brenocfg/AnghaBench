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
struct st_pctl_data {unsigned int* output_delays; int noutput_delays; unsigned int* input_delays; int ninput_delays; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static unsigned long st_pinconf_bit_to_delay(unsigned int index,
	const struct st_pctl_data *data, unsigned long output)
{
	const unsigned int *delay_times;
	int num_delay_times;

	if (output) {
		delay_times = data->output_delays;
		num_delay_times = data->noutput_delays;
	} else {
		delay_times = data->input_delays;
		num_delay_times = data->ninput_delays;
	}

	if (index < num_delay_times) {
		return delay_times[index];
	} else {
		pr_warn("Delay not found in/out delay list\n");
		return 0;
	}
}