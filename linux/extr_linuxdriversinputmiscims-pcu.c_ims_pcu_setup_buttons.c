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
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct input_dev {int keycodesize; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  keycodemax; int /*<<< orphan*/ * keycode; TYPE_1__ dev; int /*<<< orphan*/  id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct ims_pcu_buttons {struct input_dev* input; int /*<<< orphan*/ * keymap; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct ims_pcu {int device_no; int /*<<< orphan*/  dev; TYPE_2__* ctrl_intf; int /*<<< orphan*/  udev; struct ims_pcu_buttons buttons; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int IMS_PCU_KEYMAP_LEN ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned short const*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_to_input_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ims_pcu_setup_buttons(struct ims_pcu *pcu,
				 const unsigned short *keymap,
				 size_t keymap_len)
{
	struct ims_pcu_buttons *buttons = &pcu->buttons;
	struct input_dev *input;
	int i;
	int error;

	input = input_allocate_device();
	if (!input) {
		dev_err(pcu->dev,
			"Not enough memory for input input device\n");
		return -ENOMEM;
	}

	snprintf(buttons->name, sizeof(buttons->name),
		 "IMS PCU#%d Button Interface", pcu->device_no);

	usb_make_path(pcu->udev, buttons->phys, sizeof(buttons->phys));
	strlcat(buttons->phys, "/input0", sizeof(buttons->phys));

	memcpy(buttons->keymap, keymap, sizeof(*keymap) * keymap_len);

	input->name = buttons->name;
	input->phys = buttons->phys;
	usb_to_input_id(pcu->udev, &input->id);
	input->dev.parent = &pcu->ctrl_intf->dev;

	input->keycode = buttons->keymap;
	input->keycodemax = ARRAY_SIZE(buttons->keymap);
	input->keycodesize = sizeof(buttons->keymap[0]);

	__set_bit(EV_KEY, input->evbit);
	for (i = 0; i < IMS_PCU_KEYMAP_LEN; i++)
		__set_bit(buttons->keymap[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);

	error = input_register_device(input);
	if (error) {
		dev_err(pcu->dev,
			"Failed to register buttons input device: %d\n",
			error);
		input_free_device(input);
		return error;
	}

	buttons->input = input;
	return 0;
}