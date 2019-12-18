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
struct dvb_usb_adapter {TYPE_1__* fe_adap; TYPE_2__* dev; } ;
struct dib0700_state {int fw_use_new_i2c_api; int disable_streaming_master_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; struct dib0700_state* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIO0 ; 
 int /*<<< orphan*/  GPIO10 ; 
 int /*<<< orphan*/  GPIO2 ; 
 int /*<<< orphan*/  GPIO3 ; 
 int /*<<< orphan*/  GPIO4 ; 
 int /*<<< orphan*/  GPIO6 ; 
 int /*<<< orphan*/  GPIO7 ; 
 int /*<<< orphan*/  GPIO9 ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/  dib0700_set_gpio (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pinnacle_801e_config ; 
 int /*<<< orphan*/  s5h1411_attach ; 

__attribute__((used)) static int s5h1411_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dib0700_state *st = adap->dev->priv;

	/* Make use of the new i2c functions from FW 1.20 */
	st->fw_use_new_i2c_api = 1;

	/* The s5h1411 requires the dib0700 to not be in master mode */
	st->disable_streaming_master_mode = 1;

	/* All msleep values taken from Windows USB trace */
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 0);
	dib0700_set_gpio(adap->dev, GPIO3, GPIO_OUT, 0);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(400);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msleep(60);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO2, GPIO_OUT, 0);
	msleep(30);

	/* Put the CX25843 to sleep for now since we're in digital mode */
	dib0700_set_gpio(adap->dev, GPIO2, GPIO_OUT, 1);

	/* GPIOs are initialized, do the attach */
	adap->fe_adap[0].fe = dvb_attach(s5h1411_attach, &pinnacle_801e_config,
			      &adap->dev->i2c_adap);
	return adap->fe_adap[0].fe == NULL ? -ENODEV : 0;
}