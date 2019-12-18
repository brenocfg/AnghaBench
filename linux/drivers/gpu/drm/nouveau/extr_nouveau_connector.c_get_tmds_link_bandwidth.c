#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct nouveau_encoder {struct dcb_output* dcb; } ;
struct TYPE_12__ {int chipset; scalar_t__ family; } ;
struct TYPE_13__ {TYPE_5__ info; } ;
struct TYPE_14__ {TYPE_6__ device; } ;
struct nouveau_drm {TYPE_7__ client; } ;
struct TYPE_9__ {scalar_t__ supported; } ;
struct TYPE_10__ {TYPE_2__ scrambling; } ;
struct TYPE_11__ {TYPE_3__ scdc; } ;
struct drm_display_info {int max_tmds_clock; TYPE_4__ hdmi; } ;
struct TYPE_8__ {struct drm_display_info display_info; } ;
struct nouveau_connector {TYPE_1__ base; int /*<<< orphan*/  edid; struct nouveau_encoder* detected_encoder; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
struct dcb_output {scalar_t__ location; scalar_t__ duallink_possible; } ;

/* Variables and functions */
 scalar_t__ DCB_LOC_ON_CHIP ; 
 scalar_t__ NV_DEVICE_INFO_V0_FERMI ; 
 scalar_t__ NV_DEVICE_INFO_V0_KEPLER ; 
 scalar_t__ drm_detect_hdmi_monitor (int /*<<< orphan*/ ) ; 
 int min (int,int const) ; 
 struct nouveau_connector* nouveau_connector (struct drm_connector*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 scalar_t__ nouveau_duallink ; 
 int nouveau_hdmimhz ; 

__attribute__((used)) static unsigned
get_tmds_link_bandwidth(struct drm_connector *connector)
{
	struct nouveau_connector *nv_connector = nouveau_connector(connector);
	struct nouveau_encoder *nv_encoder = nv_connector->detected_encoder;
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	struct dcb_output *dcb = nv_connector->detected_encoder->dcb;
	struct drm_display_info *info = NULL;
	unsigned duallink_scale =
		nouveau_duallink && nv_encoder->dcb->duallink_possible ? 2 : 1;

	if (drm_detect_hdmi_monitor(nv_connector->edid)) {
		info = &nv_connector->base.display_info;
		duallink_scale = 1;
	}

	if (info) {
		if (nouveau_hdmimhz > 0)
			return nouveau_hdmimhz * 1000;
		/* Note: these limits are conservative, some Fermi's
		 * can do 297 MHz. Unclear how this can be determined.
		 */
		if (drm->client.device.info.chipset >= 0x120) {
			const int max_tmds_clock =
				info->hdmi.scdc.scrambling.supported ?
				594000 : 340000;
			return info->max_tmds_clock ?
				min(info->max_tmds_clock, max_tmds_clock) :
				max_tmds_clock;
		}
		if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_KEPLER)
			return 297000;
		if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_FERMI)
			return 225000;
	}

	if (dcb->location != DCB_LOC_ON_CHIP ||
	    drm->client.device.info.chipset >= 0x46)
		return 165000 * duallink_scale;
	else if (drm->client.device.info.chipset >= 0x40)
		return 155000 * duallink_scale;
	else if (drm->client.device.info.chipset >= 0x18)
		return 135000 * duallink_scale;
	else
		return 112000 * duallink_scale;
}