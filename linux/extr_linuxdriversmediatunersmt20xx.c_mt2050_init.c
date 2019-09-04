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
struct microtune_priv {int /*<<< orphan*/  i2c_props; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct microtune_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mt2050_tuner_ops ; 
 int /*<<< orphan*/  tuner_dbg (char*,unsigned char) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_recv (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_send (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int mt2050_init(struct dvb_frontend *fe)
{
	struct microtune_priv *priv = fe->tuner_priv;
	unsigned char buf[2];

	buf[0] = 6;
	buf[1] = 0x10;
	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2); /* power */

	buf[0] = 0x0f;
	buf[1] = 0x0f;
	tuner_i2c_xfer_send(&priv->i2c_props, buf, 2); /* m1lo */

	buf[0] = 0x0d;
	tuner_i2c_xfer_send(&priv->i2c_props, buf, 1);
	tuner_i2c_xfer_recv(&priv->i2c_props, buf, 1);

	tuner_dbg("mt2050: sro is %x\n", buf[0]);

	memcpy(&fe->ops.tuner_ops, &mt2050_tuner_ops, sizeof(struct dvb_tuner_ops));

	return 0;
}