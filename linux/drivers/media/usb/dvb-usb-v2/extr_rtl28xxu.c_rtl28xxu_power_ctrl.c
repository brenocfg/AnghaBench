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
struct rtl28xxu_dev {scalar_t__ chip_id; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_RTL2831U ; 
 struct rtl28xxu_dev* d_to_priv (struct dvb_usb_device*) ; 
 int rtl2831u_power_ctrl (struct dvb_usb_device*,int) ; 
 int rtl2832u_power_ctrl (struct dvb_usb_device*,int) ; 

__attribute__((used)) static int rtl28xxu_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	struct rtl28xxu_dev *dev = d_to_priv(d);

	if (dev->chip_id == CHIP_ID_RTL2831U)
		return rtl2831u_power_ctrl(d, onoff);
	else
		return rtl2832u_power_ctrl(d, onoff);
}