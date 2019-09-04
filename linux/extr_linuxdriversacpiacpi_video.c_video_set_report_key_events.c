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
struct dmi_system_id {scalar_t__ driver_data; } ;

/* Variables and functions */
 int report_key_events ; 

__attribute__((used)) static int video_set_report_key_events(const struct dmi_system_id *id)
{
	if (report_key_events == -1)
		report_key_events = (uintptr_t)id->driver_data;
	return 0;
}