#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_mode_get_encoder {int /*<<< orphan*/  possible_clones; int /*<<< orphan*/  possible_crtcs; int /*<<< orphan*/  encoder_id; int /*<<< orphan*/  encoder_type; scalar_t__ crtc_id; } ;
struct drm_file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {int /*<<< orphan*/  possible_clones; int /*<<< orphan*/  possible_crtcs; TYPE_3__ base; int /*<<< orphan*/  encoder_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  connection_mutex; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct TYPE_4__ {scalar_t__ id; } ;
struct drm_crtc {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_encoder* drm_encoder_find (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 struct drm_crtc* drm_encoder_get_crtc (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_lease_filter_crtcs (struct drm_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_lease_held (struct drm_file*,scalar_t__) ; 
 int /*<<< orphan*/  drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 

int drm_mode_getencoder(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	struct drm_mode_get_encoder *enc_resp = data;
	struct drm_encoder *encoder;
	struct drm_crtc *crtc;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	encoder = drm_encoder_find(dev, file_priv, enc_resp->encoder_id);
	if (!encoder)
		return -ENOENT;

	drm_modeset_lock(&dev->mode_config.connection_mutex, NULL);
	crtc = drm_encoder_get_crtc(encoder);
	if (crtc && drm_lease_held(file_priv, crtc->base.id))
		enc_resp->crtc_id = crtc->base.id;
	else
		enc_resp->crtc_id = 0;
	drm_modeset_unlock(&dev->mode_config.connection_mutex);

	enc_resp->encoder_type = encoder->encoder_type;
	enc_resp->encoder_id = encoder->base.id;
	enc_resp->possible_crtcs = drm_lease_filter_crtcs(file_priv,
							  encoder->possible_crtcs);
	enc_resp->possible_clones = encoder->possible_clones;

	return 0;
}