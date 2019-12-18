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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_property_blob {struct drm_mode_rect* data; int /*<<< orphan*/  length; } ;
struct drm_mode_rect {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void set_damage_blob(struct drm_property_blob *damage_blob,
			    struct drm_mode_rect *r, uint32_t size)
{
	damage_blob->length = size;
	damage_blob->data = r;
}