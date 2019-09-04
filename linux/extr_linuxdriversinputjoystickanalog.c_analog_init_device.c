#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int product; int version; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct input_dev {int* evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct analog_port {int* axes; int /*<<< orphan*/  buttons; int /*<<< orphan*/  initial; int /*<<< orphan*/  fuzz; TYPE_3__* gameport; } ;
struct analog {int mask; struct input_dev* dev; int /*<<< orphan*/ * buttons; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {char* phys; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ANALOG_BTNS_CHF ; 
 int ANALOG_BTN_TL ; 
 int ANALOG_GAMEPAD ; 
 int ANALOG_HBTN_CHF ; 
 int ANALOG_SAITEK ; 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_GAMEPORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GAMEPORT_ID_VENDOR_ANALOG ; 
 int* analog_axes ; 
 int /*<<< orphan*/  analog_close ; 
 int /*<<< orphan*/  analog_decode (struct analog*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* analog_exts ; 
 int* analog_hats ; 
 int /*<<< orphan*/ * analog_joy_btn ; 
 int /*<<< orphan*/  analog_name (struct analog*) ; 
 int /*<<< orphan*/  analog_open ; 
 int /*<<< orphan*/ * analog_pad_btn ; 
 int /*<<< orphan*/ * analog_pads ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct analog_port*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 

__attribute__((used)) static int analog_init_device(struct analog_port *port, struct analog *analog, int index)
{
	struct input_dev *input_dev;
	int i, j, t, v, w, x, y, z;
	int error;

	analog_name(analog);
	snprintf(analog->phys, sizeof(analog->phys),
		 "%s/input%d", port->gameport->phys, index);
	analog->buttons = (analog->mask & ANALOG_GAMEPAD) ? analog_pad_btn : analog_joy_btn;

	analog->dev = input_dev = input_allocate_device();
	if (!input_dev)
		return -ENOMEM;

	input_dev->name = analog->name;
	input_dev->phys = analog->phys;
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.vendor = GAMEPORT_ID_VENDOR_ANALOG;
	input_dev->id.product = analog->mask >> 4;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &port->gameport->dev;

	input_set_drvdata(input_dev, port);

	input_dev->open = analog_open;
	input_dev->close = analog_close;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	for (i = j = 0; i < 4; i++)
		if (analog->mask & (1 << i)) {

			t = analog_axes[j];
			x = port->axes[i];
			y = (port->axes[0] + port->axes[1]) >> 1;
			z = y - port->axes[i];
			z = z > 0 ? z : -z;
			v = (x >> 3);
			w = (x >> 3);

			if ((i == 2 || i == 3) && (j == 2 || j == 3) && (z > (y >> 3)))
				x = y;

			if (analog->mask & ANALOG_SAITEK) {
				if (i == 2) x = port->axes[i];
				v = x - (x >> 2);
				w = (x >> 4);
			}

			input_set_abs_params(input_dev, t, v, (x << 1) - v, port->fuzz, w);
			j++;
		}

	for (i = j = 0; i < 3; i++)
		if (analog->mask & analog_exts[i])
			for (x = 0; x < 2; x++) {
				t = analog_hats[j++];
				input_set_abs_params(input_dev, t, -1, 1, 0, 0);
			}

	for (i = j = 0; i < 4; i++)
		if (analog->mask & (0x10 << i))
			set_bit(analog->buttons[j++], input_dev->keybit);

	if (analog->mask & ANALOG_BTNS_CHF)
		for (i = 0; i < 2; i++)
			set_bit(analog->buttons[j++], input_dev->keybit);

	if (analog->mask & ANALOG_HBTN_CHF)
		for (i = 0; i < 4; i++)
			set_bit(analog->buttons[j++], input_dev->keybit);

	for (i = 0; i < 4; i++)
		if (analog->mask & (ANALOG_BTN_TL << i))
			set_bit(analog_pads[i], input_dev->keybit);

	analog_decode(analog, port->axes, port->initial, port->buttons);

	error = input_register_device(analog->dev);
	if (error) {
		input_free_device(analog->dev);
		return error;
	}

	return 0;
}