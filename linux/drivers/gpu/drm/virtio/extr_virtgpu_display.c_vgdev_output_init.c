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
struct TYPE_3__ {void* height; void* width; } ;
struct TYPE_4__ {TYPE_1__ r; void* enabled; } ;
struct drm_crtc {int dummy; } ;
struct drm_encoder {int possible_crtcs; } ;
struct drm_connector {int dummy; } ;
struct virtio_gpu_output {int index; TYPE_2__ info; struct drm_crtc crtc; struct drm_encoder enc; struct drm_connector conn; } ;
struct virtio_gpu_device {scalar_t__ has_edid; struct virtio_gpu_output* outputs; struct drm_device* ddev; } ;
struct drm_plane {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_VIRTUAL ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_CURSOR ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 scalar_t__ IS_ERR (struct drm_plane*) ; 
 int PTR_ERR (struct drm_plane*) ; 
 int XRES_DEF ; 
 int YRES_DEF ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  drm_connector_attach_edid_property (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_gpu_conn_helper_funcs ; 
 int /*<<< orphan*/  virtio_gpu_connector_funcs ; 
 int /*<<< orphan*/  virtio_gpu_crtc_funcs ; 
 int /*<<< orphan*/  virtio_gpu_crtc_helper_funcs ; 
 int /*<<< orphan*/  virtio_gpu_enc_funcs ; 
 int /*<<< orphan*/  virtio_gpu_enc_helper_funcs ; 
 struct drm_plane* virtio_gpu_plane_init (struct virtio_gpu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vgdev_output_init(struct virtio_gpu_device *vgdev, int index)
{
	struct drm_device *dev = vgdev->ddev;
	struct virtio_gpu_output *output = vgdev->outputs + index;
	struct drm_connector *connector = &output->conn;
	struct drm_encoder *encoder = &output->enc;
	struct drm_crtc *crtc = &output->crtc;
	struct drm_plane *primary, *cursor;

	output->index = index;
	if (index == 0) {
		output->info.enabled = cpu_to_le32(true);
		output->info.r.width = cpu_to_le32(XRES_DEF);
		output->info.r.height = cpu_to_le32(YRES_DEF);
	}

	primary = virtio_gpu_plane_init(vgdev, DRM_PLANE_TYPE_PRIMARY, index);
	if (IS_ERR(primary))
		return PTR_ERR(primary);
	cursor = virtio_gpu_plane_init(vgdev, DRM_PLANE_TYPE_CURSOR, index);
	if (IS_ERR(cursor))
		return PTR_ERR(cursor);
	drm_crtc_init_with_planes(dev, crtc, primary, cursor,
				  &virtio_gpu_crtc_funcs, NULL);
	drm_crtc_helper_add(crtc, &virtio_gpu_crtc_helper_funcs);

	drm_connector_init(dev, connector, &virtio_gpu_connector_funcs,
			   DRM_MODE_CONNECTOR_VIRTUAL);
	drm_connector_helper_add(connector, &virtio_gpu_conn_helper_funcs);
	if (vgdev->has_edid)
		drm_connector_attach_edid_property(connector);

	drm_encoder_init(dev, encoder, &virtio_gpu_enc_funcs,
			 DRM_MODE_ENCODER_VIRTUAL, NULL);
	drm_encoder_helper_add(encoder, &virtio_gpu_enc_helper_funcs);
	encoder->possible_crtcs = 1 << index;

	drm_connector_attach_encoder(connector, encoder);
	drm_connector_register(connector);
	return 0;
}