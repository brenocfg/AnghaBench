#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nouveau_encoder {TYPE_1__* dcb; struct i2c_adapter* i2c; } ;
struct nouveau_drm {int dummy; } ;
struct nouveau_connector {scalar_t__ type; TYPE_2__* edid; int /*<<< orphan*/  aux; } ;
struct i2c_adapter {int dummy; } ;
struct drm_encoder_helper_funcs {scalar_t__ (* detect ) (struct drm_encoder*,struct drm_connector*) ;} ;
struct drm_encoder {struct drm_encoder_helper_funcs* helper_private; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_connector {int /*<<< orphan*/  name; struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_8__ {int input; } ;
struct TYPE_7__ {int type; } ;

/* Variables and functions */
 scalar_t__ DCB_CONNECTOR_LVDS ; 
 int DCB_OUTPUT_ANALOG ; 
 int DCB_OUTPUT_TMDS ; 
 int DCB_OUTPUT_TV ; 
 int DRM_EDID_INPUT_DIGITAL ; 
 int EACCES ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,int /*<<< orphan*/ ) ; 
 int VGA_SWITCHEROO_CAN_SWITCH_DDC ; 
 scalar_t__ connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,TYPE_2__*) ; 
 int /*<<< orphan*/  drm_dp_cec_set_edid (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* drm_get_edid (struct drm_connector*,struct i2c_adapter*) ; 
 TYPE_2__* drm_get_edid_switcheroo (struct drm_connector*,struct i2c_adapter*) ; 
 scalar_t__ drm_kms_helper_is_poll_worker () ; 
 struct nouveau_encoder* find_encoder (struct drm_connector*,int) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 struct nouveau_connector* nouveau_connector (struct drm_connector*) ; 
 struct nouveau_encoder* nouveau_connector_ddc_detect (struct drm_connector*) ; 
 struct nouveau_encoder* nouveau_connector_of_detect (struct drm_connector*) ; 
 int /*<<< orphan*/  nouveau_connector_set_encoder (struct drm_connector*,struct nouveau_encoder*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_tv_disable ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct drm_encoder*,struct drm_connector*) ; 
 struct drm_encoder* to_drm_encoder (struct nouveau_encoder*) ; 
 int vga_switcheroo_handler_flags () ; 

__attribute__((used)) static enum drm_connector_status
nouveau_connector_detect(struct drm_connector *connector, bool force)
{
	struct drm_device *dev = connector->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_connector *nv_connector = nouveau_connector(connector);
	struct nouveau_encoder *nv_encoder = NULL;
	struct nouveau_encoder *nv_partner;
	struct i2c_adapter *i2c;
	int type;
	int ret;
	enum drm_connector_status conn_status = connector_status_disconnected;

	/* Cleanup the previous EDID block. */
	if (nv_connector->edid) {
		drm_connector_update_edid_property(connector, NULL);
		kfree(nv_connector->edid);
		nv_connector->edid = NULL;
	}

	/* Outputs are only polled while runtime active, so resuming the
	 * device here is unnecessary (and would deadlock upon runtime suspend
	 * because it waits for polling to finish). We do however, want to
	 * prevent the autosuspend timer from elapsing during this operation
	 * if possible.
	 */
	if (drm_kms_helper_is_poll_worker()) {
		pm_runtime_get_noresume(dev->dev);
	} else {
		ret = pm_runtime_get_sync(dev->dev);
		if (ret < 0 && ret != -EACCES)
			return conn_status;
	}

	nv_encoder = nouveau_connector_ddc_detect(connector);
	if (nv_encoder && (i2c = nv_encoder->i2c) != NULL) {
		if ((vga_switcheroo_handler_flags() &
		     VGA_SWITCHEROO_CAN_SWITCH_DDC) &&
		    nv_connector->type == DCB_CONNECTOR_LVDS)
			nv_connector->edid = drm_get_edid_switcheroo(connector,
								     i2c);
		else
			nv_connector->edid = drm_get_edid(connector, i2c);

		drm_connector_update_edid_property(connector,
							nv_connector->edid);
		if (!nv_connector->edid) {
			NV_ERROR(drm, "DDC responded, but no EDID for %s\n",
				 connector->name);
			goto detect_analog;
		}

		/* Override encoder type for DVI-I based on whether EDID
		 * says the display is digital or analog, both use the
		 * same i2c channel so the value returned from ddc_detect
		 * isn't necessarily correct.
		 */
		nv_partner = NULL;
		if (nv_encoder->dcb->type == DCB_OUTPUT_TMDS)
			nv_partner = find_encoder(connector, DCB_OUTPUT_ANALOG);
		if (nv_encoder->dcb->type == DCB_OUTPUT_ANALOG)
			nv_partner = find_encoder(connector, DCB_OUTPUT_TMDS);

		if (nv_partner && ((nv_encoder->dcb->type == DCB_OUTPUT_ANALOG &&
				    nv_partner->dcb->type == DCB_OUTPUT_TMDS) ||
				   (nv_encoder->dcb->type == DCB_OUTPUT_TMDS &&
				    nv_partner->dcb->type == DCB_OUTPUT_ANALOG))) {
			if (nv_connector->edid->input & DRM_EDID_INPUT_DIGITAL)
				type = DCB_OUTPUT_TMDS;
			else
				type = DCB_OUTPUT_ANALOG;

			nv_encoder = find_encoder(connector, type);
		}

		nouveau_connector_set_encoder(connector, nv_encoder);
		conn_status = connector_status_connected;
		drm_dp_cec_set_edid(&nv_connector->aux, nv_connector->edid);
		goto out;
	}

	nv_encoder = nouveau_connector_of_detect(connector);
	if (nv_encoder) {
		nouveau_connector_set_encoder(connector, nv_encoder);
		conn_status = connector_status_connected;
		goto out;
	}

detect_analog:
	nv_encoder = find_encoder(connector, DCB_OUTPUT_ANALOG);
	if (!nv_encoder && !nouveau_tv_disable)
		nv_encoder = find_encoder(connector, DCB_OUTPUT_TV);
	if (nv_encoder && force) {
		struct drm_encoder *encoder = to_drm_encoder(nv_encoder);
		const struct drm_encoder_helper_funcs *helper =
						encoder->helper_private;

		if (helper->detect(encoder, connector) ==
						connector_status_connected) {
			nouveau_connector_set_encoder(connector, nv_encoder);
			conn_status = connector_status_connected;
			goto out;
		}

	}

 out:

	pm_runtime_mark_last_busy(dev->dev);
	pm_runtime_put_autosuspend(dev->dev);

	return conn_status;
}