#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_vbtn_priv {TYPE_3__* input_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {char* name; TYPE_2__ id; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 struct intel_vbtn_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 TYPE_3__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 int input_register_device (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_vbtn_keymap ; 
 int sparse_keymap_setup (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_vbtn_input_setup(struct platform_device *device)
{
	struct intel_vbtn_priv *priv = dev_get_drvdata(&device->dev);
	int ret;

	priv->input_dev = devm_input_allocate_device(&device->dev);
	if (!priv->input_dev)
		return -ENOMEM;

	ret = sparse_keymap_setup(priv->input_dev, intel_vbtn_keymap, NULL);
	if (ret)
		return ret;

	priv->input_dev->dev.parent = &device->dev;
	priv->input_dev->name = "Intel Virtual Button driver";
	priv->input_dev->id.bustype = BUS_HOST;

	return input_register_device(priv->input_dev);
}