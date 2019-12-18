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
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;

/* Variables and functions */
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ max_counter_value ; 

__attribute__((used)) static int use_hw_sample_counter(struct comedi_cmd *cmd)
{
/* disable for now until I work out a race */
	return 0;

	if (cmd->stop_src == TRIG_COUNT && cmd->stop_arg <= max_counter_value)
		return 1;

	return 0;
}