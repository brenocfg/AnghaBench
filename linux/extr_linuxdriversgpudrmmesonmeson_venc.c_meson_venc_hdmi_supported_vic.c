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
struct meson_hdmi_venc_vic_mode {int vic; scalar_t__ mode; } ;

/* Variables and functions */
 struct meson_hdmi_venc_vic_mode* meson_hdmi_venc_vic_modes ; 

bool meson_venc_hdmi_supported_vic(int vic)
{
	struct meson_hdmi_venc_vic_mode *vmode = meson_hdmi_venc_vic_modes;

	while (vmode->vic && vmode->mode) {
		if (vmode->vic == vic)
			return true;
		vmode++;
	}

	return false;
}