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
struct dvb_usb_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  XD_MP2IF_DMX_CTRL ; 
 int af9005_write_ofdm_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int af9005_write_register_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  deb_info (char*,...) ; 

__attribute__((used)) static int af9005_pid_filter_control(struct dvb_usb_adapter *adap, int onoff)
{
	int ret;
	deb_info("pid filter control  onoff %d\n", onoff);
	if (onoff) {
		ret =
		    af9005_write_ofdm_register(adap->dev, XD_MP2IF_DMX_CTRL, 1);
		if (ret)
			return ret;
		ret =
		    af9005_write_register_bits(adap->dev,
					       XD_MP2IF_DMX_CTRL, 1, 1, 1);
		if (ret)
			return ret;
		ret =
		    af9005_write_ofdm_register(adap->dev, XD_MP2IF_DMX_CTRL, 1);
	} else
		ret =
		    af9005_write_ofdm_register(adap->dev, XD_MP2IF_DMX_CTRL, 0);
	if (ret)
		return ret;
	deb_info("pid filter control ok\n");
	return 0;
}