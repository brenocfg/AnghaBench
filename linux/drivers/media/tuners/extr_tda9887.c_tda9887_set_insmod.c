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
struct tda9887_priv {char* data; } ;
struct dvb_frontend {struct tda9887_priv* analog_demod_priv; } ;

/* Variables and functions */
 scalar_t__ UNSET ; 
 int adjust ; 
 char cOutputPort1Inactive ; 
 char cOutputPort2Inactive ; 
 char cQSS ; 
 char cTopMask ; 
 scalar_t__ port1 ; 
 scalar_t__ port2 ; 
 scalar_t__ qss ; 

__attribute__((used)) static int tda9887_set_insmod(struct dvb_frontend *fe)
{
	struct tda9887_priv *priv = fe->analog_demod_priv;
	char *buf = priv->data;

	if (UNSET != port1) {
		if (port1)
			buf[1] |= cOutputPort1Inactive;
		else
			buf[1] &= ~cOutputPort1Inactive;
	}
	if (UNSET != port2) {
		if (port2)
			buf[1] |= cOutputPort2Inactive;
		else
			buf[1] &= ~cOutputPort2Inactive;
	}

	if (UNSET != qss) {
		if (qss)
			buf[1] |= cQSS;
		else
			buf[1] &= ~cQSS;
	}

	if (adjust < 0x20) {
		buf[2] &= ~cTopMask;
		buf[2] |= adjust;
	}
	return 0;
}