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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ida {int dummy; } ;
struct drm_mode_config {struct ida connector_ida; int /*<<< orphan*/  prop_crtc_id; int /*<<< orphan*/  tile_property; int /*<<< orphan*/  non_desktop_property; int /*<<< orphan*/  link_status_property; int /*<<< orphan*/  dpms_property; int /*<<< orphan*/  connector_list_lock; int /*<<< orphan*/  num_connector; int /*<<< orphan*/  connector_list; } ;
struct drm_device {struct drm_mode_config mode_config; } ;
struct drm_connector_funcs {int /*<<< orphan*/  atomic_duplicate_state; int /*<<< orphan*/  atomic_destroy_state; } ;
struct TYPE_7__ {int /*<<< orphan*/ * properties; } ;
struct TYPE_6__ {int /*<<< orphan*/  panel_orientation; } ;
struct drm_connector {int index; int connector_type; int connector_type_id; TYPE_2__ base; int /*<<< orphan*/ * debugfs_entry; int /*<<< orphan*/  head; TYPE_1__ display_info; int /*<<< orphan*/  status; int /*<<< orphan*/ * tile_blob_ptr; int /*<<< orphan*/ * edid_blob_ptr; int /*<<< orphan*/  mutex; int /*<<< orphan*/  modes; int /*<<< orphan*/  probed_modes; int /*<<< orphan*/  name; struct drm_connector_funcs const* funcs; struct drm_device* dev; int /*<<< orphan*/  properties; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; struct ida ida; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_ATOMIC ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int) ; 
 int DRM_MODE_CONNECTOR_VIRTUAL ; 
 int DRM_MODE_CONNECTOR_WRITEBACK ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_CONNECTOR ; 
 int /*<<< orphan*/  DRM_MODE_PANEL_ORIENTATION_UNKNOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __drm_mode_object_add (struct drm_device*,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connector_status_unknown ; 
 int /*<<< orphan*/  drm_connector_attach_edid_property (struct drm_connector*) ; 
 TYPE_4__* drm_connector_enum_list ; 
 int /*<<< orphan*/  drm_connector_free ; 
 int /*<<< orphan*/  drm_connector_get_cmdline_mode (struct drm_connector*) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_object_unregister (struct drm_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  drm_object_attach_property (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ida_simple_get (struct ida*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (struct ida*,int) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int drm_connector_init(struct drm_device *dev,
		       struct drm_connector *connector,
		       const struct drm_connector_funcs *funcs,
		       int connector_type)
{
	struct drm_mode_config *config = &dev->mode_config;
	int ret;
	struct ida *connector_ida =
		&drm_connector_enum_list[connector_type].ida;

	WARN_ON(drm_drv_uses_atomic_modeset(dev) &&
		(!funcs->atomic_destroy_state ||
		 !funcs->atomic_duplicate_state));

	ret = __drm_mode_object_add(dev, &connector->base,
				    DRM_MODE_OBJECT_CONNECTOR,
				    false, drm_connector_free);
	if (ret)
		return ret;

	connector->base.properties = &connector->properties;
	connector->dev = dev;
	connector->funcs = funcs;

	/* connector index is used with 32bit bitmasks */
	ret = ida_simple_get(&config->connector_ida, 0, 32, GFP_KERNEL);
	if (ret < 0) {
		DRM_DEBUG_KMS("Failed to allocate %s connector index: %d\n",
			      drm_connector_enum_list[connector_type].name,
			      ret);
		goto out_put;
	}
	connector->index = ret;
	ret = 0;

	connector->connector_type = connector_type;
	connector->connector_type_id =
		ida_simple_get(connector_ida, 1, 0, GFP_KERNEL);
	if (connector->connector_type_id < 0) {
		ret = connector->connector_type_id;
		goto out_put_id;
	}
	connector->name =
		kasprintf(GFP_KERNEL, "%s-%d",
			  drm_connector_enum_list[connector_type].name,
			  connector->connector_type_id);
	if (!connector->name) {
		ret = -ENOMEM;
		goto out_put_type_id;
	}

	INIT_LIST_HEAD(&connector->probed_modes);
	INIT_LIST_HEAD(&connector->modes);
	mutex_init(&connector->mutex);
	connector->edid_blob_ptr = NULL;
	connector->tile_blob_ptr = NULL;
	connector->status = connector_status_unknown;
	connector->display_info.panel_orientation =
		DRM_MODE_PANEL_ORIENTATION_UNKNOWN;

	drm_connector_get_cmdline_mode(connector);

	/* We should add connectors at the end to avoid upsetting the connector
	 * index too much. */
	spin_lock_irq(&config->connector_list_lock);
	list_add_tail(&connector->head, &config->connector_list);
	config->num_connector++;
	spin_unlock_irq(&config->connector_list_lock);

	if (connector_type != DRM_MODE_CONNECTOR_VIRTUAL &&
	    connector_type != DRM_MODE_CONNECTOR_WRITEBACK)
		drm_connector_attach_edid_property(connector);

	drm_object_attach_property(&connector->base,
				      config->dpms_property, 0);

	drm_object_attach_property(&connector->base,
				   config->link_status_property,
				   0);

	drm_object_attach_property(&connector->base,
				   config->non_desktop_property,
				   0);
	drm_object_attach_property(&connector->base,
				   config->tile_property,
				   0);

	if (drm_core_check_feature(dev, DRIVER_ATOMIC)) {
		drm_object_attach_property(&connector->base, config->prop_crtc_id, 0);
	}

	connector->debugfs_entry = NULL;
out_put_type_id:
	if (ret)
		ida_simple_remove(connector_ida, connector->connector_type_id);
out_put_id:
	if (ret)
		ida_simple_remove(&config->connector_ida, connector->index);
out_put:
	if (ret)
		drm_mode_object_unregister(dev, &connector->base);

	return ret;
}