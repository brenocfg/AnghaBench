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
struct sil164_priv {int /*<<< orphan*/  duallink_slave; } ;
struct i2c_client {int dummy; } ;
struct drm_encoder_slave {int /*<<< orphan*/ * slave_funcs; struct sil164_priv* slave_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sil164_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sil164_detect_slave (struct i2c_client*) ; 
 int /*<<< orphan*/  sil164_encoder_funcs ; 

__attribute__((used)) static int
sil164_encoder_init(struct i2c_client *client,
		    struct drm_device *dev,
		    struct drm_encoder_slave *encoder)
{
	struct sil164_priv *priv;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	encoder->slave_priv = priv;
	encoder->slave_funcs = &sil164_encoder_funcs;

	priv->duallink_slave = sil164_detect_slave(client);

	return 0;
}