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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * drm_named_modes_whitelist ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool drm_named_mode_is_in_whitelist(const char *mode, unsigned int size)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(drm_named_modes_whitelist); i++)
		if (!strncmp(mode, drm_named_modes_whitelist[i], size))
			return true;

	return false;
}