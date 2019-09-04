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
struct sc27xx_adc_linear_graph {int volt0; int volt1; int adc1; int adc0; } ;

/* Variables and functions */

__attribute__((used)) static int sc27xx_adc_to_volt(const struct sc27xx_adc_linear_graph *graph,
			      int raw_adc)
{
	int tmp;

	tmp = (graph->volt0 - graph->volt1) * (raw_adc - graph->adc1);
	tmp /= (graph->adc0 - graph->adc1);
	tmp += graph->volt1;

	return tmp < 0 ? 0 : tmp;
}