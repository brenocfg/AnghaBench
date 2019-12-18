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
struct tvnorm {int std; char b; char c; char e; int /*<<< orphan*/  name; } ;
struct tda9887_priv {char* data; scalar_t__ mode; scalar_t__ audmode; int std; } ;
struct dvb_frontend {struct tda9887_priv* analog_demod_priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tvnorm*) ; 
 scalar_t__ V4L2_TUNER_MODE_MONO ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 struct tvnorm radio_mono ; 
 struct tvnorm radio_stereo ; 
 int /*<<< orphan*/  tuner_dbg (char*,...) ; 
 struct tvnorm* tvnorms ; 

__attribute__((used)) static int tda9887_set_tvnorm(struct dvb_frontend *fe)
{
	struct tda9887_priv *priv = fe->analog_demod_priv;
	struct tvnorm *norm = NULL;
	char *buf = priv->data;
	int i;

	if (priv->mode == V4L2_TUNER_RADIO) {
		if (priv->audmode == V4L2_TUNER_MODE_MONO)
			norm = &radio_mono;
		else
			norm = &radio_stereo;
	} else {
		for (i = 0; i < ARRAY_SIZE(tvnorms); i++) {
			if (tvnorms[i].std & priv->std) {
				norm = tvnorms+i;
				break;
			}
		}
	}
	if (NULL == norm) {
		tuner_dbg("Unsupported tvnorm entry - audio muted\n");
		return -1;
	}

	tuner_dbg("configure for: %s\n", norm->name);
	buf[1] = norm->b;
	buf[2] = norm->c;
	buf[3] = norm->e;
	return 0;
}