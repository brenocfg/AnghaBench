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
struct rockchip_lvds {int /*<<< orphan*/  panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 struct rockchip_lvds* encoder_to_lvds (struct drm_encoder*) ; 
 int /*<<< orphan*/  rockchip_lvds_poweroff (struct rockchip_lvds*) ; 

__attribute__((used)) static void rockchip_lvds_encoder_disable(struct drm_encoder *encoder)
{
	struct rockchip_lvds *lvds = encoder_to_lvds(encoder);

	drm_panel_disable(lvds->panel);
	rockchip_lvds_poweroff(lvds);
	drm_panel_unprepare(lvds->panel);
}