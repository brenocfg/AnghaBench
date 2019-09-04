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
struct intel_driver_caps {int /*<<< orphan*/  scheduler; int /*<<< orphan*/  has_logical_contexts; } ;
struct drm_printer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

void intel_driver_caps_print(const struct intel_driver_caps *caps,
			     struct drm_printer *p)
{
	drm_printf(p, "Has logical contexts? %s\n",
		   yesno(caps->has_logical_contexts));
	drm_printf(p, "scheduler: %x\n", caps->scheduler);
}