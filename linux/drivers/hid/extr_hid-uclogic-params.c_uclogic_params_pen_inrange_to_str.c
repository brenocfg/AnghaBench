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
typedef  enum uclogic_params_pen_inrange { ____Placeholder_uclogic_params_pen_inrange } uclogic_params_pen_inrange ;

/* Variables and functions */
#define  UCLOGIC_PARAMS_PEN_INRANGE_INVERTED 130 
#define  UCLOGIC_PARAMS_PEN_INRANGE_NONE 129 
#define  UCLOGIC_PARAMS_PEN_INRANGE_NORMAL 128 

const char *uclogic_params_pen_inrange_to_str(
			enum uclogic_params_pen_inrange inrange)
{
	switch (inrange) {
	case UCLOGIC_PARAMS_PEN_INRANGE_NORMAL:
		return "normal";
	case UCLOGIC_PARAMS_PEN_INRANGE_INVERTED:
		return "inverted";
	case UCLOGIC_PARAMS_PEN_INRANGE_NONE:
		return "none";
	default:
		return NULL;
	}
}