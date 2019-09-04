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
struct i2c_client {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct ch7006_state {int dummy; } ;
struct ch7006_priv {int last_dpms; struct ch7006_state state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH7006_POWER ; 
 int /*<<< orphan*/  ch7006_dbg (struct i2c_client*,char*) ; 
 int /*<<< orphan*/  ch7006_load_reg (struct i2c_client*,struct ch7006_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ch7006_setup_power_state (struct drm_encoder*) ; 
 struct i2c_client* drm_i2c_encoder_get_client (struct drm_encoder*) ; 
 struct ch7006_priv* to_ch7006_priv (struct drm_encoder*) ; 

__attribute__((used)) static void  ch7006_encoder_dpms(struct drm_encoder *encoder, int mode)
{
	struct i2c_client *client = drm_i2c_encoder_get_client(encoder);
	struct ch7006_priv *priv = to_ch7006_priv(encoder);
	struct ch7006_state *state = &priv->state;

	ch7006_dbg(client, "\n");

	if (mode == priv->last_dpms)
		return;
	priv->last_dpms = mode;

	ch7006_setup_power_state(encoder);

	ch7006_load_reg(client, state, CH7006_POWER);
}