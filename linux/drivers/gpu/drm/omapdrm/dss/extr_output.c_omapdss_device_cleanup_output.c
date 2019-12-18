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
struct omap_dss_device {scalar_t__ next; } ;

/* Variables and functions */
 int /*<<< orphan*/  omapdss_device_put (scalar_t__) ; 

void omapdss_device_cleanup_output(struct omap_dss_device *out)
{
	if (out->next)
		omapdss_device_put(out->next);
}