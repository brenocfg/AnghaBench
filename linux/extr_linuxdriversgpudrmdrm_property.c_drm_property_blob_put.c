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
struct drm_property_blob {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_object_put (int /*<<< orphan*/ *) ; 

void drm_property_blob_put(struct drm_property_blob *blob)
{
	if (!blob)
		return;

	drm_mode_object_put(&blob->base);
}