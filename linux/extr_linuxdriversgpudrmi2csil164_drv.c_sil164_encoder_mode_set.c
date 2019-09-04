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
struct sil164_priv {int /*<<< orphan*/  config; scalar_t__ duallink_slave; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 scalar_t__ drm_i2c_encoder_get_client (struct drm_encoder*) ; 
 int /*<<< orphan*/  sil164_encoder_dpms (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sil164_init_state (scalar_t__,int /*<<< orphan*/ *,int) ; 
 struct sil164_priv* to_sil164_priv (struct drm_encoder*) ; 

__attribute__((used)) static void
sil164_encoder_mode_set(struct drm_encoder *encoder,
			struct drm_display_mode *mode,
			struct drm_display_mode *adjusted_mode)
{
	struct sil164_priv *priv = to_sil164_priv(encoder);
	bool duallink = adjusted_mode->clock > 165000;

	sil164_init_state(drm_i2c_encoder_get_client(encoder),
			  &priv->config, duallink);

	if (priv->duallink_slave)
		sil164_init_state(priv->duallink_slave,
				  &priv->config, duallink);

	sil164_encoder_dpms(encoder, DRM_MODE_DPMS_ON);
}