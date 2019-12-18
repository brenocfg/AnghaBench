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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {char* name; struct i2c_adapter* adap; int /*<<< orphan*/  addr; } ;
struct tea5761_priv {TYPE_1__ i2c_props; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct tea5761_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tea5761_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tea5761_autodetection (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tea5761_tuner_ops ; 
 int /*<<< orphan*/  tuner_info (char*,char*) ; 

struct dvb_frontend *tea5761_attach(struct dvb_frontend *fe,
				    struct i2c_adapter* i2c_adap,
				    u8 i2c_addr)
{
	struct tea5761_priv *priv = NULL;

	if (tea5761_autodetection(i2c_adap, i2c_addr) != 0)
		return NULL;

	priv = kzalloc(sizeof(struct tea5761_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;
	fe->tuner_priv = priv;

	priv->i2c_props.addr = i2c_addr;
	priv->i2c_props.adap = i2c_adap;
	priv->i2c_props.name = "tea5761";

	memcpy(&fe->ops.tuner_ops, &tea5761_tuner_ops,
	       sizeof(struct dvb_tuner_ops));

	tuner_info("type set to %s\n", "Philips TEA5761HN FM Radio");

	return fe;
}