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
struct TYPE_4__ {int /*<<< orphan*/ * fops; int /*<<< orphan*/  name; int /*<<< orphan*/  minor; } ;
struct hid_sensor_custom {int /*<<< orphan*/  data_fifo; TYPE_2__ custom_dev; TYPE_1__* pdev; int /*<<< orphan*/  wait; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CUSTOM_FIFO_SIZE ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_sensor_custom_fops ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int misc_register (TYPE_2__*) ; 

__attribute__((used)) static int hid_sensor_custom_dev_if_add(struct hid_sensor_custom *sensor_inst)
{
	int ret;

	ret = kfifo_alloc(&sensor_inst->data_fifo, HID_CUSTOM_FIFO_SIZE,
			  GFP_KERNEL);
	if (ret)
		return ret;

	init_waitqueue_head(&sensor_inst->wait);

	sensor_inst->custom_dev.minor = MISC_DYNAMIC_MINOR;
	sensor_inst->custom_dev.name = dev_name(&sensor_inst->pdev->dev);
	sensor_inst->custom_dev.fops = &hid_sensor_custom_fops,
	ret = misc_register(&sensor_inst->custom_dev);
	if (ret) {
		kfifo_free(&sensor_inst->data_fifo);
		return ret;
	}
	return 0;
}