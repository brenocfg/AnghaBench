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
struct pvr2_hdw {int unit_number; } ;

/* Variables and functions */
 int PVR_NUM ; 
 int* tolerance ; 

__attribute__((used)) static unsigned int get_default_error_tolerance(struct pvr2_hdw *hdw)
{
	int unit_number = hdw->unit_number;
	int tp = 0;
	if ((unit_number >= 0) && (unit_number < PVR_NUM)) {
		tp = tolerance[unit_number];
	}
	return tp;
}