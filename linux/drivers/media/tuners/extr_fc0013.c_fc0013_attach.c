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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_adapter {int dummy; } ;
struct fc0013_priv {int dual_master; int xtal_freq; int /*<<< orphan*/  addr; struct i2c_adapter* i2c; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct fc0013_priv* tuner_priv; } ;
typedef  enum fc001x_xtal_freq { ____Placeholder_fc001x_xtal_freq } fc001x_xtal_freq ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fc0013_tuner_ops ; 
 int /*<<< orphan*/  info (char*) ; 
 struct fc0013_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct dvb_frontend *fc0013_attach(struct dvb_frontend *fe,
	struct i2c_adapter *i2c, u8 i2c_address, int dual_master,
	enum fc001x_xtal_freq xtal_freq)
{
	struct fc0013_priv *priv = NULL;

	priv = kzalloc(sizeof(struct fc0013_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;

	priv->i2c = i2c;
	priv->dual_master = dual_master;
	priv->addr = i2c_address;
	priv->xtal_freq = xtal_freq;

	info("Fitipower FC0013 successfully attached.");

	fe->tuner_priv = priv;

	memcpy(&fe->ops.tuner_ops, &fc0013_tuner_ops,
		sizeof(struct dvb_tuner_ops));

	return fe;
}