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
struct drm_device {int last_context; int /*<<< orphan*/  context_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_context_switch(struct drm_device * dev, int old, int new)
{
	if (test_and_set_bit(0, &dev->context_flag)) {
		DRM_ERROR("Reentering -- FIXME\n");
		return -EBUSY;
	}

	DRM_DEBUG("Context switch from %d to %d\n", old, new);

	if (new == dev->last_context) {
		clear_bit(0, &dev->context_flag);
		return 0;
	}

	return 0;
}