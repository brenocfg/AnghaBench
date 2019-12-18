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
struct sil164_priv {int /*<<< orphan*/  saved_slave_state; scalar_t__ duallink_slave; int /*<<< orphan*/  saved_state; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 scalar_t__ drm_i2c_encoder_get_client (struct drm_encoder*) ; 
 int /*<<< orphan*/  sil164_restore_state (scalar_t__,int /*<<< orphan*/ ) ; 
 struct sil164_priv* to_sil164_priv (struct drm_encoder*) ; 

__attribute__((used)) static void
sil164_encoder_restore(struct drm_encoder *encoder)
{
	struct sil164_priv *priv = to_sil164_priv(encoder);

	sil164_restore_state(drm_i2c_encoder_get_client(encoder),
			     priv->saved_state);

	if (priv->duallink_slave)
		sil164_restore_state(priv->duallink_slave,
				     priv->saved_slave_state);
}