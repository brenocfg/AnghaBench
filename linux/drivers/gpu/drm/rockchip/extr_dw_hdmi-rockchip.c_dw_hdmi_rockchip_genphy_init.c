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
struct rockchip_hdmi {int /*<<< orphan*/  phy; } ;
struct dw_hdmi {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_hdmi_rockchip_genphy_init(struct dw_hdmi *dw_hdmi, void *data,
			     struct drm_display_mode *mode)
{
	struct rockchip_hdmi *hdmi = (struct rockchip_hdmi *)data;

	return phy_power_on(hdmi->phy);
}