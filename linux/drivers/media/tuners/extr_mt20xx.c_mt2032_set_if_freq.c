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
struct microtune_priv {int xogc; int /*<<< orphan*/  i2c_props; } ;
struct dvb_frontend {struct microtune_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int mt2032_check_lo_lock (struct dvb_frontend*) ; 
 int mt2032_compute_freq (struct dvb_frontend*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned char*,int*,int) ; 
 int mt2032_optimize_vco (struct dvb_frontend*,int,int) ; 
 scalar_t__ optimize_vco ; 
 int /*<<< orphan*/  tuner_dbg (char*,...) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_recv (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int tuner_i2c_xfer_send (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  tuner_warn (char*,...) ; 

__attribute__((used)) static void mt2032_set_if_freq(struct dvb_frontend *fe, unsigned int rfin,
			       unsigned int if1, unsigned int if2,
			       unsigned int from, unsigned int to)
{
	unsigned char buf[21];
	int lint_try,ret,sel,lock=0;
	struct microtune_priv *priv = fe->tuner_priv;

	tuner_dbg("mt2032_set_if_freq rfin=%d if1=%d if2=%d from=%d to=%d\n",
		  rfin,if1,if2,from,to);

	buf[0]=0;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,1);
	tuner_i2c_xfer_recv(&priv->i2c_props,buf,21);

	buf[0]=0;
	ret=mt2032_compute_freq(fe,rfin,if1,if2,from,to,&buf[1],&sel,priv->xogc);
	if (ret<0)
		return;

	// send only the relevant registers per Rev. 1.2
	buf[0]=0;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,4);
	buf[5]=5;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+5,4);
	buf[11]=11;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+11,3);
	if(ret!=3)
		tuner_warn("i2c i/o error: rc == %d (should be 3)\n",ret);

	// wait for PLLs to lock (per manual), retry LINT if not.
	for(lint_try=0; lint_try<2; lint_try++) {
		lock=mt2032_check_lo_lock(fe);

		if(optimize_vco)
			lock=mt2032_optimize_vco(fe,sel,lock);
		if(lock==6) break;

		tuner_dbg("mt2032: re-init PLLs by LINT\n");
		buf[0]=7;
		buf[1]=0x80 +8+priv->xogc; // set LINT to re-init PLLs
		tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
		mdelay(10);
		buf[1]=8+priv->xogc;
		tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
	}

	if (lock!=6)
		tuner_warn("MT2032 Fatal Error: PLLs didn't lock.\n");

	buf[0]=2;
	buf[1]=0x20; // LOGC for optimal phase noise
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
	if (ret!=2)
		tuner_warn("i2c i/o error: rc == %d (should be 2)\n",ret);
}