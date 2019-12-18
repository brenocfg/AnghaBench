#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_overlay {int dummy; } ;
struct intel_crtc {TYPE_1__* config; int /*<<< orphan*/  active; } ;
struct TYPE_2__ {scalar_t__ double_wide; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int check_overlay_possible_on_crtc(struct intel_overlay *overlay,
					  struct intel_crtc *crtc)
{
	if (!crtc->active)
		return -EINVAL;

	/* can't use the overlay with double wide pipe */
	if (crtc->config->double_wide)
		return -EINVAL;

	return 0;
}