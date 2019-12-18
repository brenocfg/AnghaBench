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
struct omap_dss_device {struct omap_dss_device* next; } ;

/* Variables and functions */
 struct omap_dss_device* omapdss_device_get (struct omap_dss_device*) ; 

struct omap_dss_device *omapdss_display_get(struct omap_dss_device *output)
{
	while (output->next)
		output = output->next;

	return omapdss_device_get(output);
}