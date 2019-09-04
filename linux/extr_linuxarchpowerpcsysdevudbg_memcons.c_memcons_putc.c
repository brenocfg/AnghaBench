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
struct TYPE_2__ {char* output_pos; char* output_end; char* output_start; } ;

/* Variables and functions */
 TYPE_1__ memcons ; 
 int /*<<< orphan*/  wmb () ; 

void memcons_putc(char c)
{
	char *new_output_pos;

	*memcons.output_pos = c;
	wmb();
	new_output_pos = memcons.output_pos + 1;
	if (new_output_pos >= memcons.output_end)
		new_output_pos = memcons.output_start;

	memcons.output_pos = new_output_pos;
}