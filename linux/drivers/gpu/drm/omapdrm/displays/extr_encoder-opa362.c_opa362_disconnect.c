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
struct omap_dss_device {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  omapdss_device_disconnect (struct omap_dss_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opa362_disconnect(struct omap_dss_device *src,
			      struct omap_dss_device *dst)
{
	omapdss_device_disconnect(dst, dst->next);
}