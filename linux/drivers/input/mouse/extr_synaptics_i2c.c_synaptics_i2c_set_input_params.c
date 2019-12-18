#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct synaptics_i2c {TYPE_4__* client; struct input_dev* input; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  version; int /*<<< orphan*/  bustype; } ;
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  close; int /*<<< orphan*/  open; TYPE_3__ dev; TYPE_2__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; TYPE_1__* adapter; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BUS_I2C ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  INFO_QUERY_REG0 ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (struct input_dev*,struct synaptics_i2c*) ; 
 int /*<<< orphan*/  synaptics_i2c_close ; 
 int /*<<< orphan*/  synaptics_i2c_open ; 
 int /*<<< orphan*/  synaptics_i2c_word_get (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void synaptics_i2c_set_input_params(struct synaptics_i2c *touch)
{
	struct input_dev *input = touch->input;

	input->name = touch->client->name;
	input->phys = touch->client->adapter->name;
	input->id.bustype = BUS_I2C;
	input->id.version = synaptics_i2c_word_get(touch->client,
						   INFO_QUERY_REG0);
	input->dev.parent = &touch->client->dev;
	input->open = synaptics_i2c_open;
	input->close = synaptics_i2c_close;
	input_set_drvdata(input, touch);

	/* Register the device as mouse */
	__set_bit(EV_REL, input->evbit);
	__set_bit(REL_X, input->relbit);
	__set_bit(REL_Y, input->relbit);

	/* Register device's buttons and keys */
	__set_bit(EV_KEY, input->evbit);
	__set_bit(BTN_LEFT, input->keybit);
}