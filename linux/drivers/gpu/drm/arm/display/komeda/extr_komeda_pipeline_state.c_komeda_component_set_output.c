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
typedef  int /*<<< orphan*/  u8 ;
struct komeda_component_output {int /*<<< orphan*/  output_port; struct komeda_component* component; } ;
struct komeda_component {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
komeda_component_set_output(struct komeda_component_output *output,
			    struct komeda_component *comp,
			    u8 output_port)
{
	output->component = comp;
	output->output_port = output_port;
}