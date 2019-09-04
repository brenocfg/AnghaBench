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
struct videomode {int /*<<< orphan*/  member_0; } ;
struct omap_dss_driver {scalar_t__ (* read_edid ) (struct omap_dss_device*,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_size ) (struct omap_dss_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* get_timings ) (struct omap_dss_device*,struct videomode*) ;} ;
struct omap_dss_device {int /*<<< orphan*/  name; struct omap_dss_driver* driver; } ;
struct omap_connector {int /*<<< orphan*/  hdmi_mode; struct omap_dss_device* dssdev; } ;
struct drm_display_mode {int type; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct drm_connector {TYPE_1__ display_info; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_EDID ; 
 int drm_add_edid_modes (struct drm_connector*,void*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,void*) ; 
 int /*<<< orphan*/  drm_detect_hdmi_monitor (void*) ; 
 int /*<<< orphan*/  drm_display_mode_from_videomode (struct videomode*,struct drm_display_mode*) ; 
 scalar_t__ drm_edid_is_valid (void*) ; 
 struct drm_display_mode* drm_mode_create (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct omap_dss_device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*,struct videomode*) ; 
 int /*<<< orphan*/  stub3 (struct omap_dss_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct omap_connector* to_omap_connector (struct drm_connector*) ; 

__attribute__((used)) static int omap_connector_get_modes(struct drm_connector *connector)
{
	struct omap_connector *omap_connector = to_omap_connector(connector);
	struct omap_dss_device *dssdev = omap_connector->dssdev;
	struct omap_dss_driver *dssdrv = dssdev->driver;
	struct drm_device *dev = connector->dev;
	int n = 0;

	DBG("%s", omap_connector->dssdev->name);

	/* if display exposes EDID, then we parse that in the normal way to
	 * build table of supported modes.. otherwise (ie. fixed resolution
	 * LCD panels) we just return a single mode corresponding to the
	 * currently configured timings:
	 */
	if (dssdrv->read_edid) {
		void *edid = kzalloc(MAX_EDID, GFP_KERNEL);

		if (!edid)
			return 0;

		if ((dssdrv->read_edid(dssdev, edid, MAX_EDID) > 0) &&
				drm_edid_is_valid(edid)) {
			drm_connector_update_edid_property(
					connector, edid);
			n = drm_add_edid_modes(connector, edid);

			omap_connector->hdmi_mode =
				drm_detect_hdmi_monitor(edid);
		} else {
			drm_connector_update_edid_property(
					connector, NULL);
		}

		kfree(edid);
	} else {
		struct drm_display_mode *mode = drm_mode_create(dev);
		struct videomode vm = {0};

		if (!mode)
			return 0;

		dssdrv->get_timings(dssdev, &vm);

		drm_display_mode_from_videomode(&vm, mode);

		mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
		drm_mode_set_name(mode);
		drm_mode_probed_add(connector, mode);

		if (dssdrv->get_size) {
			dssdrv->get_size(dssdev,
					 &connector->display_info.width_mm,
					 &connector->display_info.height_mm);
		}

		n = 1;
	}

	return n;
}