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
struct tda9887_priv {int standby; int /*<<< orphan*/  std; int /*<<< orphan*/  audmode; int /*<<< orphan*/  mode; } ;
struct dvb_frontend {struct tda9887_priv* analog_demod_priv; } ;
struct analog_parameters {int /*<<< orphan*/  std; int /*<<< orphan*/  audmode; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  tda9887_configure (struct dvb_frontend*) ; 

__attribute__((used)) static void tda9887_set_params(struct dvb_frontend *fe,
			       struct analog_parameters *params)
{
	struct tda9887_priv *priv = fe->analog_demod_priv;

	priv->standby = false;
	priv->mode    = params->mode;
	priv->audmode = params->audmode;
	priv->std     = params->std;
	tda9887_configure(fe);
}