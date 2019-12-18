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
struct tegra_dpaux {int dummy; } ;
struct drm_dp_aux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_dpaux_pad_power_down (struct tegra_dpaux*) ; 
 struct tegra_dpaux* to_dpaux (struct drm_dp_aux*) ; 

int drm_dp_aux_disable(struct drm_dp_aux *aux)
{
	struct tegra_dpaux *dpaux = to_dpaux(aux);

	tegra_dpaux_pad_power_down(dpaux);

	return 0;
}