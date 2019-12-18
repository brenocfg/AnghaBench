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
struct saa7134_dev {int tuner_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TUNER_PHILIPS_TDA8290 130 
#define  TUNER_XC2028 129 
#define  TUNER_XC5000 128 
 int /*<<< orphan*/  pr_err (char*) ; 
 int saa7134_tda8290_callback (struct saa7134_dev*,int,int) ; 
 int saa7134_xc2028_callback (struct saa7134_dev*,int,int) ; 
 int saa7134_xc5000_callback (struct saa7134_dev*,int,int) ; 

int saa7134_tuner_callback(void *priv, int component, int command, int arg)
{
	struct saa7134_dev *dev = priv;

	if (dev != NULL) {
		switch (dev->tuner_type) {
		case TUNER_PHILIPS_TDA8290:
			return saa7134_tda8290_callback(dev, command, arg);
		case TUNER_XC2028:
			return saa7134_xc2028_callback(dev, command, arg);
		case TUNER_XC5000:
			return saa7134_xc5000_callback(dev, command, arg);
		}
	} else {
		pr_err("saa7134: Error - device struct undefined.\n");
		return -EINVAL;
	}
	return -EINVAL;
}