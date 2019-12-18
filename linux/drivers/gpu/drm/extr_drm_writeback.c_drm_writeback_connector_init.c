#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int id; } ;
struct drm_connector {char* name; TYPE_2__ base; scalar_t__ interlace_allowed; } ;
struct drm_writeback_connector {int /*<<< orphan*/  encoder; struct drm_property_blob* pixel_formats_blob_ptr; int /*<<< orphan*/  timeline_name; int /*<<< orphan*/  fence_lock; int /*<<< orphan*/  fence_context; int /*<<< orphan*/  job_lock; int /*<<< orphan*/  job_queue; struct drm_connector base; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct drm_property_blob {TYPE_1__ base; } ;
struct drm_mode_config {int /*<<< orphan*/  writeback_pixel_formats_property; int /*<<< orphan*/  writeback_fb_id_property; int /*<<< orphan*/  writeback_out_fence_ptr_property; } ;
struct drm_encoder_helper_funcs {int dummy; } ;
struct drm_device {struct drm_mode_config mode_config; } ;
struct drm_connector_funcs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_WRITEBACK ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_VIRTUAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct drm_property_blob*) ; 
 int PTR_ERR (struct drm_property_blob*) ; 
 int create_writeback_properties (struct drm_device*) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int drm_connector_attach_encoder (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int drm_connector_init (struct drm_device*,struct drm_connector*,struct drm_connector_funcs const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (int /*<<< orphan*/ *,struct drm_encoder_helper_funcs const*) ; 
 int drm_encoder_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_object_attach_property (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_blob_put (struct drm_property_blob*) ; 
 struct drm_property_blob* drm_property_create_blob (struct drm_device*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  drm_writeback_encoder_funcs ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int drm_writeback_connector_init(struct drm_device *dev,
				 struct drm_writeback_connector *wb_connector,
				 const struct drm_connector_funcs *con_funcs,
				 const struct drm_encoder_helper_funcs *enc_helper_funcs,
				 const u32 *formats, int n_formats)
{
	struct drm_property_blob *blob;
	struct drm_connector *connector = &wb_connector->base;
	struct drm_mode_config *config = &dev->mode_config;
	int ret = create_writeback_properties(dev);

	if (ret != 0)
		return ret;

	blob = drm_property_create_blob(dev, n_formats * sizeof(*formats),
					formats);
	if (IS_ERR(blob))
		return PTR_ERR(blob);

	drm_encoder_helper_add(&wb_connector->encoder, enc_helper_funcs);
	ret = drm_encoder_init(dev, &wb_connector->encoder,
			       &drm_writeback_encoder_funcs,
			       DRM_MODE_ENCODER_VIRTUAL, NULL);
	if (ret)
		goto fail;

	connector->interlace_allowed = 0;

	ret = drm_connector_init(dev, connector, con_funcs,
				 DRM_MODE_CONNECTOR_WRITEBACK);
	if (ret)
		goto connector_fail;

	ret = drm_connector_attach_encoder(connector,
						&wb_connector->encoder);
	if (ret)
		goto attach_fail;

	INIT_LIST_HEAD(&wb_connector->job_queue);
	spin_lock_init(&wb_connector->job_lock);

	wb_connector->fence_context = dma_fence_context_alloc(1);
	spin_lock_init(&wb_connector->fence_lock);
	snprintf(wb_connector->timeline_name,
		 sizeof(wb_connector->timeline_name),
		 "CONNECTOR:%d-%s", connector->base.id, connector->name);

	drm_object_attach_property(&connector->base,
				   config->writeback_out_fence_ptr_property, 0);

	drm_object_attach_property(&connector->base,
				   config->writeback_fb_id_property, 0);

	drm_object_attach_property(&connector->base,
				   config->writeback_pixel_formats_property,
				   blob->base.id);
	wb_connector->pixel_formats_blob_ptr = blob;

	return 0;

attach_fail:
	drm_connector_cleanup(connector);
connector_fail:
	drm_encoder_cleanup(&wb_connector->encoder);
fail:
	drm_property_blob_put(blob);
	return ret;
}