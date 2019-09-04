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
struct tegra_sor {scalar_t__ aux; } ;
struct tegra_output {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct tegra_output* connector_to_output (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_dp_aux_disable (scalar_t__) ; 
 int /*<<< orphan*/  drm_dp_aux_enable (scalar_t__) ; 
 int tegra_output_connector_get_modes (struct drm_connector*) ; 
 struct tegra_sor* to_sor (struct tegra_output*) ; 

__attribute__((used)) static int tegra_sor_connector_get_modes(struct drm_connector *connector)
{
	struct tegra_output *output = connector_to_output(connector);
	struct tegra_sor *sor = to_sor(output);
	int err;

	if (sor->aux)
		drm_dp_aux_enable(sor->aux);

	err = tegra_output_connector_get_modes(connector);

	if (sor->aux)
		drm_dp_aux_disable(sor->aux);

	return err;
}