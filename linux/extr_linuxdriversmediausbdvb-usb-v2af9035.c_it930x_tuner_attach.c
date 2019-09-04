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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct state {int /*<<< orphan*/  i2c_adapter_demod; } ;
struct si2157_config {int if_port; int /*<<< orphan*/  fe; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct dvb_usb_adapter {int id; int /*<<< orphan*/ * fe; } ;
typedef  int /*<<< orphan*/  si2157_config ;

/* Variables and functions */
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int af9035_add_i2c_dev (struct dvb_usb_device*,char*,int,struct si2157_config*,int /*<<< orphan*/ ) ; 
 int af9035_wr_reg (struct dvb_usb_device*,int,int) ; 
 int af9035_wr_reg_mask (struct dvb_usb_device*,int,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct si2157_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int it930x_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct usb_interface *intf = d->intf;
	int ret;
	struct si2157_config si2157_config;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	/* I2C master bus 2 clock speed 300k */
	ret = af9035_wr_reg(d, 0x00f6a7, 0x07);
	if (ret < 0)
		goto err;

	/* I2C master bus 1,3 clock speed 300k */
	ret = af9035_wr_reg(d, 0x00f103, 0x07);
	if (ret < 0)
		goto err;

	/* set gpio11 low */
	ret = af9035_wr_reg_mask(d, 0xd8d4, 0x01, 0x01);
	if (ret < 0)
		goto err;

	ret = af9035_wr_reg_mask(d, 0xd8d5, 0x01, 0x01);
	if (ret < 0)
		goto err;

	ret = af9035_wr_reg_mask(d, 0xd8d3, 0x01, 0x01);
	if (ret < 0)
		goto err;

	/* Tuner enable using gpiot2_en, gpiot2_on and gpiot2_o (reset) */
	ret = af9035_wr_reg_mask(d, 0xd8b8, 0x01, 0x01);
	if (ret < 0)
		goto err;

	ret = af9035_wr_reg_mask(d, 0xd8b9, 0x01, 0x01);
	if (ret < 0)
		goto err;

	ret = af9035_wr_reg_mask(d, 0xd8b7, 0x00, 0x01);
	if (ret < 0)
		goto err;

	msleep(200);

	ret = af9035_wr_reg_mask(d, 0xd8b7, 0x01, 0x01);
	if (ret < 0)
		goto err;

	memset(&si2157_config, 0, sizeof(si2157_config));
	si2157_config.fe = adap->fe[0];
	si2157_config.if_port = 1;
	ret = af9035_add_i2c_dev(d, "si2157", 0x63,
			&si2157_config, state->i2c_adapter_demod);

	if (ret)
		goto err;

	return 0;

err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);

	return ret;
}