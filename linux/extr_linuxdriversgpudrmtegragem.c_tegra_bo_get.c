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
struct tegra_bo {int /*<<< orphan*/  gem; } ;
struct host1x_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_get (int /*<<< orphan*/ *) ; 
 struct tegra_bo* host1x_to_tegra_bo (struct host1x_bo*) ; 

__attribute__((used)) static struct host1x_bo *tegra_bo_get(struct host1x_bo *bo)
{
	struct tegra_bo *obj = host1x_to_tegra_bo(bo);

	drm_gem_object_get(&obj->gem);

	return bo;
}