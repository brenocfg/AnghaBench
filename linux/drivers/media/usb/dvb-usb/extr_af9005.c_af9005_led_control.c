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
struct dvb_usb_device {struct af9005_device_state* priv; } ;
struct af9005_device_state {int led_state; } ;

/* Variables and functions */
 int af9005_write_register_bits (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dvb_usb_af9005_led ; 
 int /*<<< orphan*/  reg_top_lock1_len ; 
 int /*<<< orphan*/  reg_top_lock1_pos ; 
 int /*<<< orphan*/  reg_top_locken1_len ; 
 int /*<<< orphan*/  reg_top_locken1_pos ; 
 int /*<<< orphan*/  xd_p_reg_top_lock1 ; 
 int /*<<< orphan*/  xd_p_reg_top_locken1 ; 

int af9005_led_control(struct dvb_usb_device *d, int onoff)
{
	struct af9005_device_state *st = d->priv;
	int temp, ret;

	if (onoff && dvb_usb_af9005_led)
		temp = 1;
	else
		temp = 0;
	if (st->led_state != temp) {
		ret =
		    af9005_write_register_bits(d, xd_p_reg_top_locken1,
					       reg_top_locken1_pos,
					       reg_top_locken1_len, temp);
		if (ret)
			return ret;
		ret =
		    af9005_write_register_bits(d, xd_p_reg_top_lock1,
					       reg_top_lock1_pos,
					       reg_top_lock1_len, temp);
		if (ret)
			return ret;
		st->led_state = temp;
	}
	return 0;
}