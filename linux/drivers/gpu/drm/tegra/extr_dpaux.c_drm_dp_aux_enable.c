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
 int /*<<< orphan*/  DPAUX_PADCTL_FUNC_AUX ; 
 int tegra_dpaux_pad_config (struct tegra_dpaux*,int /*<<< orphan*/ ) ; 
 struct tegra_dpaux* to_dpaux (struct drm_dp_aux*) ; 

int drm_dp_aux_enable(struct drm_dp_aux *aux)
{
	struct tegra_dpaux *dpaux = to_dpaux(aux);

	return tegra_dpaux_pad_config(dpaux, DPAUX_PADCTL_FUNC_AUX);
}