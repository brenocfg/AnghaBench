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
struct drm_format_modifier_blob {int modifiers_offset; } ;
struct drm_format_modifier {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct drm_format_modifier *
modifiers_ptr(struct drm_format_modifier_blob *blob)
{
	return (struct drm_format_modifier *)(((char *)blob) + blob->modifiers_offset);
}