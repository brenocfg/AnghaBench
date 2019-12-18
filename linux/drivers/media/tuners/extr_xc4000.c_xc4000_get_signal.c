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
typedef  int u16 ;
struct xc4000_priv {scalar_t__ video_standard; int /*<<< orphan*/  lock; } ;
struct dvb_frontend {struct xc4000_priv* tuner_priv; } ;

/* Variables and functions */
 scalar_t__ XC4000_DTV6 ; 
 scalar_t__ XC4000_DTV7 ; 
 scalar_t__ XC4000_DTV7_8 ; 
 scalar_t__ XC4000_DTV8 ; 
 int /*<<< orphan*/  XREG_NOISE_LEVEL ; 
 int /*<<< orphan*/  XREG_SIGNAL_LEVEL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuner_dbg (char*,int,int) ; 
 int xc4000_readreg (struct xc4000_priv*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int xc4000_get_signal(struct dvb_frontend *fe, u16 *strength)
{
	struct xc4000_priv *priv = fe->tuner_priv;
	u16 value = 0;
	int rc;

	mutex_lock(&priv->lock);
	rc = xc4000_readreg(priv, XREG_SIGNAL_LEVEL, &value);
	mutex_unlock(&priv->lock);

	if (rc < 0)
		goto ret;

	/* Information from real testing of DVB-T and radio part,
	   coefficient for one dB is 0xff.
	 */
	tuner_dbg("Signal strength: -%ddB (%05d)\n", value >> 8, value);

	/* all known digital modes */
	if ((priv->video_standard == XC4000_DTV6) ||
	    (priv->video_standard == XC4000_DTV7) ||
	    (priv->video_standard == XC4000_DTV7_8) ||
	    (priv->video_standard == XC4000_DTV8))
		goto digital;

	/* Analog mode has NOISE LEVEL important, signal
	   depends only on gain of antenna and amplifiers,
	   but it doesn't tell anything about real quality
	   of reception.
	 */
	mutex_lock(&priv->lock);
	rc = xc4000_readreg(priv, XREG_NOISE_LEVEL, &value);
	mutex_unlock(&priv->lock);

	tuner_dbg("Noise level: %ddB (%05d)\n", value >> 8, value);

	/* highest noise level: 32dB */
	if (value >= 0x2000) {
		value = 0;
	} else {
		value = (~value << 3) & 0xffff;
	}

	goto ret;

	/* Digital mode has SIGNAL LEVEL important and real
	   noise level is stored in demodulator registers.
	 */
digital:
	/* best signal: -50dB */
	if (value <= 0x3200) {
		value = 0xffff;
	/* minimum: -114dB - should be 0x7200 but real zero is 0x713A */
	} else if (value >= 0x713A) {
		value = 0;
	} else {
		value = ~(value - 0x3200) << 2;
	}

ret:
	*strength = value;

	return rc;
}