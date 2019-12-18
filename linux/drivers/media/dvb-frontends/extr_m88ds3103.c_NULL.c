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
typedef  unsigned int u8 ;
struct m88ds3103_dev {int /*<<< orphan*/  regmap; } ;
struct dvb_frontend {struct m88ds3103_dev* demodulator_priv; } ;

/* Variables and functions */
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

int m88ds3103_get_agc_pwm(struct dvb_frontend *fe, u8 *_agc_pwm)
{
	struct m88ds3103_dev *dev = fe->demodulator_priv;
	unsigned tmp;
	int ret;

	ret = regmap_read(dev->regmap, 0x3f, &tmp);
	if (ret == 0)
		*_agc_pwm = tmp;
	return ret;
}