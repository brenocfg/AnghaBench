#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zx_vga {int connected; scalar_t__ mmio; TYPE_1__* ddc; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 scalar_t__ VGA_AUTO_DETECT_SEL ; 
 int /*<<< orphan*/  VGA_DETECT_SEL_HAS_DEVICE ; 
 int /*<<< orphan*/  VGA_DETECT_SEL_NO_DEVICE ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 struct zx_vga* to_zx_vga (struct drm_connector*) ; 
 int /*<<< orphan*/  zx_writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_vga_connector_get_modes(struct drm_connector *connector)
{
	struct zx_vga *vga = to_zx_vga(connector);
	struct edid *edid;
	int ret;

	/*
	 * Clear both detection bits to switch I2C bus from device
	 * detecting to EDID reading.
	 */
	zx_writel(vga->mmio + VGA_AUTO_DETECT_SEL, 0);

	edid = drm_get_edid(connector, &vga->ddc->adap);
	if (!edid) {
		/*
		 * If EDID reading fails, we set the device state into
		 * disconnected.  Locking is not required here, since the
		 * VGA_AUTO_DETECT_SEL register write in irq handler cannot
		 * be triggered when both detection bits are cleared as above.
		 */
		zx_writel(vga->mmio + VGA_AUTO_DETECT_SEL,
			  VGA_DETECT_SEL_NO_DEVICE);
		vga->connected = false;
		return 0;
	}

	/*
	 * As edid reading succeeds, device must be connected, so we set
	 * up detection bit for unplug interrupt here.
	 */
	zx_writel(vga->mmio + VGA_AUTO_DETECT_SEL, VGA_DETECT_SEL_HAS_DEVICE);

	drm_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	kfree(edid);

	return ret;
}