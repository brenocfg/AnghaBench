#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_hid_priv {TYPE_2__* array; } ;
struct TYPE_5__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_6__ {char* name; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 struct intel_hid_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 TYPE_2__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_array_keymap ; 
 int sparse_keymap_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_button_array_input_setup(struct platform_device *device)
{
	struct intel_hid_priv *priv = dev_get_drvdata(&device->dev);
	int ret;

	/* Setup input device for 5 button array */
	priv->array = devm_input_allocate_device(&device->dev);
	if (!priv->array)
		return -ENOMEM;

	ret = sparse_keymap_setup(priv->array, intel_array_keymap, NULL);
	if (ret)
		return ret;

	priv->array->name = "Intel HID 5 button array";
	priv->array->id.bustype = BUS_HOST;

	return input_register_device(priv->array);
}