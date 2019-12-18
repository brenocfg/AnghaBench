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
struct drm_master {struct drm_master* lessor; } ;

/* Variables and functions */

struct drm_master *drm_lease_owner(struct drm_master *master)
{
	while (master->lessor != NULL)
		master = master->lessor;
	return master;
}