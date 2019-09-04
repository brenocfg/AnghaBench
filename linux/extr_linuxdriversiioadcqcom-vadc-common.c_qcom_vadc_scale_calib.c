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
typedef  scalar_t__ u16 ;
struct vadc_linear_graph {scalar_t__ dx; int /*<<< orphan*/  dy; scalar_t__ gnd; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ div64_s64 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_vadc_scale_calib(const struct vadc_linear_graph *calib_graph,
				  u16 adc_code,
				  bool absolute,
				  s64 *scale_voltage)
{
	*scale_voltage = (adc_code - calib_graph->gnd);
	*scale_voltage *= calib_graph->dx;
	*scale_voltage = div64_s64(*scale_voltage, calib_graph->dy);
	if (absolute)
		*scale_voltage += calib_graph->dx;

	if (*scale_voltage < 0)
		*scale_voltage = 0;
}