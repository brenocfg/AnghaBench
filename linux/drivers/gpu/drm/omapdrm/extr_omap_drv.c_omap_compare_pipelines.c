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
struct omap_drm_pipeline {scalar_t__ alias_id; } ;

/* Variables and functions */

__attribute__((used)) static int omap_compare_pipelines(const void *a, const void *b)
{
	const struct omap_drm_pipeline *pipe1 = a;
	const struct omap_drm_pipeline *pipe2 = b;

	if (pipe1->alias_id > pipe2->alias_id)
		return 1;
	else if (pipe1->alias_id < pipe2->alias_id)
		return -1;
	return 0;
}