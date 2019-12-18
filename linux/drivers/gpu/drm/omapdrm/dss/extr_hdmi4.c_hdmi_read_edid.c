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
typedef  int /*<<< orphan*/  u8 ;
struct omap_hdmi {int core_enabled; int /*<<< orphan*/  core; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int /*<<< orphan*/  cec_get_edid_phys_addr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct omap_hdmi* dssdev_to_hdmi (struct omap_dss_device*) ; 
 int /*<<< orphan*/  hdmi4_cec_set_phys_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi4_core_disable (int /*<<< orphan*/ *) ; 
 int hdmi4_core_enable (int /*<<< orphan*/ *) ; 
 int read_edid (struct omap_hdmi*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hdmi_read_edid(struct omap_dss_device *dssdev,
		u8 *edid, int len)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);
	bool need_enable;
	int r;

	need_enable = hdmi->core_enabled == false;

	if (need_enable) {
		r = hdmi4_core_enable(&hdmi->core);
		if (r)
			return r;
	}

	r = read_edid(hdmi, edid, len);
	if (r >= 256)
		hdmi4_cec_set_phys_addr(&hdmi->core,
					cec_get_edid_phys_addr(edid, r, NULL));
	else
		hdmi4_cec_set_phys_addr(&hdmi->core, CEC_PHYS_ADDR_INVALID);
	if (need_enable)
		hdmi4_core_disable(&hdmi->core);

	return r;
}