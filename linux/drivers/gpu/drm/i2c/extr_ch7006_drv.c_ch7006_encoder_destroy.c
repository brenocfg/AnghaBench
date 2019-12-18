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
struct drm_encoder {int /*<<< orphan*/  dev; } ;
struct ch7006_priv {int /*<<< orphan*/  scale_property; } ;
struct TYPE_2__ {int /*<<< orphan*/ * slave_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_i2c_encoder_destroy (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_property_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ch7006_priv*) ; 
 struct ch7006_priv* to_ch7006_priv (struct drm_encoder*) ; 
 TYPE_1__* to_encoder_slave (struct drm_encoder*) ; 

__attribute__((used)) static void ch7006_encoder_destroy(struct drm_encoder *encoder)
{
	struct ch7006_priv *priv = to_ch7006_priv(encoder);

	drm_property_destroy(encoder->dev, priv->scale_property);

	kfree(priv);
	to_encoder_slave(encoder)->slave_priv = NULL;

	drm_i2c_encoder_destroy(encoder);
}