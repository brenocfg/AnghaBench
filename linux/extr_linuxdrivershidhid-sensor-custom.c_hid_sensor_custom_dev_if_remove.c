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
struct hid_sensor_custom {int /*<<< orphan*/  data_fifo; int /*<<< orphan*/  custom_dev; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hid_sensor_custom_dev_if_remove(struct hid_sensor_custom
								*sensor_inst)
{
	wake_up(&sensor_inst->wait);
	misc_deregister(&sensor_inst->custom_dev);
	kfifo_free(&sensor_inst->data_fifo);

}