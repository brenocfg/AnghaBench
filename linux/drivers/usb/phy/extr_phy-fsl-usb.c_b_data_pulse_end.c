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

/* Variables and functions */
 int /*<<< orphan*/  fsl_otg_loc_conn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_otg_pulse_vbus () ; 

void b_data_pulse_end(unsigned long foo)
{
#ifdef HA_DATA_PULSE
#else
	fsl_otg_loc_conn(0);
#endif

	/* Do VBUS pulse after data pulse */
	fsl_otg_pulse_vbus();
}