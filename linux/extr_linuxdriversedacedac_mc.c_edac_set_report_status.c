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
 int EDAC_REPORTING_DISABLED ; 
 int EDAC_REPORTING_ENABLED ; 
 int EDAC_REPORTING_FORCE ; 
 int edac_report ; 

void edac_set_report_status(int new)
{
	if (new == EDAC_REPORTING_ENABLED ||
	    new == EDAC_REPORTING_DISABLED ||
	    new == EDAC_REPORTING_FORCE)
		edac_report = new;
}