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
struct tegra_drm_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_drm_context_free (struct tegra_drm_context*) ; 

__attribute__((used)) static int tegra_drm_context_cleanup(int id, void *p, void *data)
{
	struct tegra_drm_context *context = p;

	tegra_drm_context_free(context);

	return 0;
}