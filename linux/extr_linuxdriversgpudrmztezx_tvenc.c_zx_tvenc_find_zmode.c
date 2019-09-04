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
struct zx_tvenc_mode {int /*<<< orphan*/  mode; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct zx_tvenc_mode**) ; 
 scalar_t__ drm_mode_equal (struct drm_display_mode*,int /*<<< orphan*/ *) ; 
 struct zx_tvenc_mode** tvenc_modes ; 

__attribute__((used)) static const struct zx_tvenc_mode *
zx_tvenc_find_zmode(struct drm_display_mode *mode)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(tvenc_modes); i++) {
		const struct zx_tvenc_mode *zmode = tvenc_modes[i];

		if (drm_mode_equal(mode, &zmode->mode))
			return zmode;
	}

	return NULL;
}