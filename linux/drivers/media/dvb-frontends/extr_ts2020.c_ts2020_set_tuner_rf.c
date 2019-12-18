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
struct ts2020_priv {int /*<<< orphan*/  regmap; } ;
struct dvb_frontend {struct ts2020_priv* tuner_priv; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,unsigned int) ; 
 int ts2020_tuner_gate_ctrl (struct dvb_frontend*,int) ; 

__attribute__((used)) static int ts2020_set_tuner_rf(struct dvb_frontend *fe)
{
	struct ts2020_priv *dev = fe->tuner_priv;
	int ret;
	unsigned int utmp;

	ret = regmap_read(dev->regmap, 0x3d, &utmp);
	if (ret)
		return ret;

	utmp &= 0x7f;
	if (utmp < 0x16)
		utmp = 0xa1;
	else if (utmp == 0x16)
		utmp = 0x99;
	else
		utmp = 0xf9;

	regmap_write(dev->regmap, 0x60, utmp);
	ret = ts2020_tuner_gate_ctrl(fe, 0x08);

	return ret;
}