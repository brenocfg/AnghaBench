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
typedef  int /*<<< orphan*/  uint32_t ;
struct i2c_client {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct ch7006_tv_norm_info {int subc_freq; } ;
struct ch7006_state {int dummy; } ;
struct ch7006_priv {size_t norm; struct ch7006_mode* mode; struct ch7006_state state; } ;
struct ch7006_mode {int subc_coeff; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH7006_SUBC_INC0 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC1 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC2 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC3 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC4 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC5 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC6 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC7 ; 
 int /*<<< orphan*/  ch7006_dbg (struct i2c_client*,char*,int /*<<< orphan*/ ) ; 
 struct ch7006_tv_norm_info* ch7006_tv_norms ; 
 struct i2c_client* drm_i2c_encoder_get_client (struct drm_encoder*) ; 
 int /*<<< orphan*/  round_fixed (int) ; 
 int /*<<< orphan*/  setbitf (struct ch7006_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ch7006_priv* to_ch7006_priv (struct drm_encoder*) ; 

void ch7006_setup_subcarrier(struct drm_encoder *encoder)
{
	struct i2c_client *client = drm_i2c_encoder_get_client(encoder);
	struct ch7006_priv *priv = to_ch7006_priv(encoder);
	struct ch7006_state *state = &priv->state;
	const struct ch7006_tv_norm_info *norm = &ch7006_tv_norms[priv->norm];
	const struct ch7006_mode *mode = priv->mode;
	uint32_t subc_inc;

	subc_inc = round_fixed((mode->subc_coeff >> 8)
			       * (norm->subc_freq >> 24));

	setbitf(state, CH7006_SUBC_INC0, 28, subc_inc);
	setbitf(state, CH7006_SUBC_INC1, 24, subc_inc);
	setbitf(state, CH7006_SUBC_INC2, 20, subc_inc);
	setbitf(state, CH7006_SUBC_INC3, 16, subc_inc);
	setbitf(state, CH7006_SUBC_INC4, 12, subc_inc);
	setbitf(state, CH7006_SUBC_INC5, 8, subc_inc);
	setbitf(state, CH7006_SUBC_INC6, 4, subc_inc);
	setbitf(state, CH7006_SUBC_INC7, 0, subc_inc);

	ch7006_dbg(client, "subcarrier inc: %u\n", subc_inc);
}