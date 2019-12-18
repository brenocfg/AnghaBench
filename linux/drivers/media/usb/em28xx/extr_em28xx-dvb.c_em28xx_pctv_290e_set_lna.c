#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct em28xx_i2c_bus {struct em28xx* dev; } ;
struct em28xx_dvb {int /*<<< orphan*/  lna_gpio; } ;
struct em28xx {TYPE_2__* intf; struct em28xx_dvb* dvb; } ;
struct dtv_frontend_properties {int lna; } ;
struct dvb_frontend {TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct em28xx_i2c_bus* priv; } ;

/* Variables and functions */
 unsigned long GPIOF_OUT_INIT_HIGH ; 
 unsigned long GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request_one (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int em28xx_pctv_290e_set_lna(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct em28xx_i2c_bus *i2c_bus = fe->dvb->priv;
	struct em28xx *dev = i2c_bus->dev;
#ifdef CONFIG_GPIOLIB
	struct em28xx_dvb *dvb = dev->dvb;
	int ret;
	unsigned long flags;

	if (c->lna == 1)
		flags = GPIOF_OUT_INIT_HIGH; /* enable LNA */
	else
		flags = GPIOF_OUT_INIT_LOW; /* disable LNA */

	ret = gpio_request_one(dvb->lna_gpio, flags, NULL);
	if (ret)
		dev_err(&dev->intf->dev, "gpio request failed %d\n", ret);
	else
		gpio_free(dvb->lna_gpio);

	return ret;
#else
	dev_warn(&dev->intf->dev, "%s: LNA control is disabled (lna=%u)\n",
		 KBUILD_MODNAME, c->lna);
	return 0;
#endif
}