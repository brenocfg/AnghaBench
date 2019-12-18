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
struct surface3_ts_data {TYPE_2__* spi; int /*<<< orphan*/  pen_tool; struct input_dev* pen_input_dev; } ;
struct TYPE_3__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; char* phys; TYPE_1__ id; int /*<<< orphan*/  propbit; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_SPI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 int /*<<< orphan*/  INPUT_PROP_POINTER ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct input_dev* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_abs_set_res (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int surface3_spi_create_pen_input(struct surface3_ts_data *data)
{
	struct input_dev *input;
	int error;

	input = devm_input_allocate_device(&data->spi->dev);
	if (!input)
		return -ENOMEM;

	data->pen_input_dev = input;
	data->pen_tool = BTN_TOOL_PEN;

	__set_bit(INPUT_PROP_DIRECT, input->propbit);
	__set_bit(INPUT_PROP_POINTER, input->propbit);
	input_set_abs_params(input, ABS_X, 0, 9600, 0, 0);
	input_abs_set_res(input, ABS_X, 40);
	input_set_abs_params(input, ABS_Y, 0, 7200, 0, 0);
	input_abs_set_res(input, ABS_Y, 48);
	input_set_abs_params(input, ABS_PRESSURE, 0, 1024, 0, 0);
	input_set_capability(input, EV_KEY, BTN_TOUCH);
	input_set_capability(input, EV_KEY, BTN_STYLUS);
	input_set_capability(input, EV_KEY, BTN_TOOL_PEN);
	input_set_capability(input, EV_KEY, BTN_TOOL_RUBBER);

	input->name = "Surface3 SPI Pen Input";
	input->phys = "input/ts";
	input->id.bustype = BUS_SPI;
	input->id.vendor = 0x045e;     /* Microsoft */
	input->id.product = 0x0002;
	input->id.version = 0x0000;

	error = input_register_device(input);
	if (error) {
		dev_err(&data->spi->dev,
			"Failed to register input device: %d", error);
		return error;
	}

	return 0;
}