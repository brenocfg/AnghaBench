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
struct dvb_usb_adapter {size_t id; TYPE_2__* dev; TYPE_1__* fe_adap; } ;
struct dib0700_state {int* mt2060_if1; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; struct dib0700_state* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DIB3000P_I2C_ADDRESS ; 
 int ENODEV ; 
 int /*<<< orphan*/  GPIO0 ; 
 int /*<<< orphan*/  GPIO10 ; 
 int /*<<< orphan*/  GPIO6 ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/ * bristol_dib3000mc_config ; 
 int /*<<< orphan*/  dib0700_set_gpio (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dib3000mc_attach ; 
 scalar_t__ dib3000mc_i2c_enumeration (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ force_lna_activation ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int bristol_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dib0700_state *st = adap->dev->priv;
	if (adap->id == 0) {
		dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 0); msleep(10);
		dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 1); msleep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0); msleep(10);
		dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1); msleep(10);

		if (force_lna_activation)
			dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
		else
			dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 0);

		if (dib3000mc_i2c_enumeration(&adap->dev->i2c_adap, 2, DEFAULT_DIB3000P_I2C_ADDRESS, bristol_dib3000mc_config) != 0) {
			dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0); msleep(10);
			return -ENODEV;
		}
	}
	st->mt2060_if1[adap->id] = 1220;
	return (adap->fe_adap[0].fe = dvb_attach(dib3000mc_attach, &adap->dev->i2c_adap,
		(10 + adap->id) << 1, &bristol_dib3000mc_config[adap->id])) == NULL ? -ENODEV : 0;
}