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
struct tda9887_priv {int /*<<< orphan*/ * data; int /*<<< orphan*/  i2c_props; scalar_t__ standby; } ;
struct dvb_frontend {struct tda9887_priv* analog_demod_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cForcedMuteAudioON ; 
 int /*<<< orphan*/  cOutputPort1Inactive ; 
 int /*<<< orphan*/  cOutputPort2Inactive ; 
 int debug ; 
 int /*<<< orphan*/  dump_write_message (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  tda9887_do_config (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tda9887_set_insmod (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tda9887_set_tvnorm (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tda9887_status (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tuner_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tuner_i2c_xfer_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tuner_info (char*,int) ; 

__attribute__((used)) static void tda9887_configure(struct dvb_frontend *fe)
{
	struct tda9887_priv *priv = fe->analog_demod_priv;
	int rc;

	memset(priv->data,0,sizeof(priv->data));
	tda9887_set_tvnorm(fe);

	/* A note on the port settings:
	   These settings tend to depend on the specifics of the board.
	   By default they are set to inactive (bit value 1) by this driver,
	   overwriting any changes made by the tvnorm. This means that it
	   is the responsibility of the module using the tda9887 to set
	   these values in case of changes in the tvnorm.
	   In many cases port 2 should be made active (0) when selecting
	   SECAM-L, and port 2 should remain inactive (1) for SECAM-L'.

	   For the other standards the tda9887 application note says that
	   the ports should be set to active (0), but, again, that may
	   differ depending on the precise hardware configuration.
	 */
	priv->data[1] |= cOutputPort1Inactive;
	priv->data[1] |= cOutputPort2Inactive;

	tda9887_do_config(fe);
	tda9887_set_insmod(fe);

	if (priv->standby)
		priv->data[1] |= cForcedMuteAudioON;

	tuner_dbg("writing: b=0x%02x c=0x%02x e=0x%02x\n",
		  priv->data[1], priv->data[2], priv->data[3]);
	if (debug > 1)
		dump_write_message(fe, priv->data);

	if (4 != (rc = tuner_i2c_xfer_send(&priv->i2c_props,priv->data,4)))
		tuner_info("i2c i/o error: rc == %d (should be 4)\n", rc);

	if (debug > 2) {
		msleep_interruptible(1000);
		tda9887_status(fe);
	}
}