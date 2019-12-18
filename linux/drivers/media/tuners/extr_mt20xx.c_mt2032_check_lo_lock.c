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
struct microtune_priv {int /*<<< orphan*/  i2c_props; } ;
struct dvb_frontend {struct microtune_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  tuner_dbg (char*,unsigned char) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_recv (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_send (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mt2032_check_lo_lock(struct dvb_frontend *fe)
{
	struct microtune_priv *priv = fe->tuner_priv;
	int try,lock=0;
	unsigned char buf[2];

	for(try=0;try<10;try++) {
		buf[0]=0x0e;
		tuner_i2c_xfer_send(&priv->i2c_props,buf,1);
		tuner_i2c_xfer_recv(&priv->i2c_props,buf,1);
		tuner_dbg("mt2032 Reg.E=0x%02x\n",buf[0]);
		lock=buf[0] &0x06;

		if (lock==6)
			break;

		tuner_dbg("mt2032: pll wait 1ms for lock (0x%2x)\n",buf[0]);
		udelay(1000);
	}
	return lock;
}