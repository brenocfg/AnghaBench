#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ family; int chipset; } ;
struct TYPE_7__ {TYPE_2__ info; } ;
struct TYPE_8__ {TYPE_3__ device; } ;
struct nouveau_drm {TYPE_4__ client; } ;
struct nouveau_connector {TYPE_1__* detected_encoder; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
struct dcb_output {scalar_t__ location; } ;
struct TYPE_5__ {struct dcb_output* dcb; } ;

/* Variables and functions */
 scalar_t__ DCB_LOC_ON_CHIP ; 
 scalar_t__ NV_DEVICE_INFO_V0_FERMI ; 
 scalar_t__ NV_DEVICE_INFO_V0_KEPLER ; 
 struct nouveau_connector* nouveau_connector (struct drm_connector*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int nouveau_hdmimhz ; 

__attribute__((used)) static unsigned
get_tmds_link_bandwidth(struct drm_connector *connector, bool hdmi)
{
	struct nouveau_connector *nv_connector = nouveau_connector(connector);
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	struct dcb_output *dcb = nv_connector->detected_encoder->dcb;

	if (hdmi) {
		if (nouveau_hdmimhz > 0)
			return nouveau_hdmimhz * 1000;
		/* Note: these limits are conservative, some Fermi's
		 * can do 297 MHz. Unclear how this can be determined.
		 */
		if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_KEPLER)
			return 297000;
		if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_FERMI)
			return 225000;
	}
	if (dcb->location != DCB_LOC_ON_CHIP ||
	    drm->client.device.info.chipset >= 0x46)
		return 165000;
	else if (drm->client.device.info.chipset >= 0x40)
		return 155000;
	else if (drm->client.device.info.chipset >= 0x18)
		return 135000;
	else
		return 112000;
}