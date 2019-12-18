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
struct usb_xpad {int /*<<< orphan*/  xtype; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
#define  ABS_HAT0X 135 
#define  ABS_HAT0Y 134 
#define  ABS_RX 133 
#define  ABS_RY 132 
#define  ABS_RZ 131 
#define  ABS_X 130 
#define  ABS_Y 129 
#define  ABS_Z 128 
 int /*<<< orphan*/  XTYPE_XBOXONE ; 
 struct usb_xpad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,short,int,int,int,int) ; 

__attribute__((used)) static void xpad_set_up_abs(struct input_dev *input_dev, signed short abs)
{
	struct usb_xpad *xpad = input_get_drvdata(input_dev);

	switch (abs) {
	case ABS_X:
	case ABS_Y:
	case ABS_RX:
	case ABS_RY:	/* the two sticks */
		input_set_abs_params(input_dev, abs, -32768, 32767, 16, 128);
		break;
	case ABS_Z:
	case ABS_RZ:	/* the triggers (if mapped to axes) */
		if (xpad->xtype == XTYPE_XBOXONE)
			input_set_abs_params(input_dev, abs, 0, 1023, 0, 0);
		else
			input_set_abs_params(input_dev, abs, 0, 255, 0, 0);
		break;
	case ABS_HAT0X:
	case ABS_HAT0Y:	/* the d-pad (only if dpad is mapped to axes */
		input_set_abs_params(input_dev, abs, -1, 1, 0, 0);
		break;
	default:
		input_set_abs_params(input_dev, abs, 0, 0, 0, 0);
		break;
	}
}