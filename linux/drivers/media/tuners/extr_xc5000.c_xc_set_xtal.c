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
struct xc5000_priv {int chip_id; int /*<<< orphan*/  xtal_khz; } ;
struct dvb_frontend {struct xc5000_priv* tuner_priv; } ;

/* Variables and functions */
#define  XC5000A 129 
#define  XC5000C 128 
 int xc_write_reg (struct xc5000_priv*,int,int) ; 

__attribute__((used)) static int xc_set_xtal(struct dvb_frontend *fe)
{
	struct xc5000_priv *priv = fe->tuner_priv;
	int ret = 0;

	switch (priv->chip_id) {
	default:
	case XC5000A:
		/* 32.000 MHz xtal is default */
		break;
	case XC5000C:
		switch (priv->xtal_khz) {
		default:
		case 32000:
			/* 32.000 MHz xtal is default */
			break;
		case 31875:
			/* 31.875 MHz xtal configuration */
			ret = xc_write_reg(priv, 0x000f, 0x8081);
			break;
		}
		break;
	}
	return ret;
}