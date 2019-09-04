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
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;
struct anysee_state {scalar_t__ has_ci; } ;

/* Variables and functions */
 int anysee_ci_init (struct dvb_usb_device*) ; 
 int anysee_ir_ctrl (struct dvb_usb_device*,int) ; 
 int anysee_led_ctrl (struct dvb_usb_device*,int,int) ; 
 struct anysee_state* d_to_priv (struct dvb_usb_device*) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int anysee_init(struct dvb_usb_device *d)
{
	struct anysee_state *state = d_to_priv(d);
	int ret;

	/* There is one interface with two alternate settings.
	   Alternate setting 0 is for bulk transfer.
	   Alternate setting 1 is for isochronous transfer.
	   We use bulk transfer (alternate setting 0). */
	ret = usb_set_interface(d->udev, 0, 0);
	if (ret)
		return ret;

	/* LED light */
	ret = anysee_led_ctrl(d, 0x01, 0x03);
	if (ret)
		return ret;

	/* enable IR */
	ret = anysee_ir_ctrl(d, 1);
	if (ret)
		return ret;

	/* attach CI */
	if (state->has_ci) {
		ret = anysee_ci_init(d);
		if (ret)
			return ret;
	}

	return 0;
}