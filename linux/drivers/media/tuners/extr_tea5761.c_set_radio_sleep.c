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
struct tea5761_priv {int standby; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {struct tea5761_priv* analog_demod_priv; } ;

/* Variables and functions */
 int __set_radio_freq (struct dvb_frontend*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_radio_sleep(struct dvb_frontend *fe)
{
	struct tea5761_priv *priv = fe->analog_demod_priv;

	priv->standby = true;

	return __set_radio_freq(fe, priv->frequency, false);
}