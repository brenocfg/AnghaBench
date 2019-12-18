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
struct v4l2_device {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct si4713_usb_device {struct si4713_usb_device* buffer; int /*<<< orphan*/  v4l2_dev; struct i2c_adapter i2c_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  kfree (struct si4713_usb_device*) ; 
 struct si4713_usb_device* to_si4713_dev (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_si4713_video_device_release(struct v4l2_device *v4l2_dev)
{
	struct si4713_usb_device *radio = to_si4713_dev(v4l2_dev);
	struct i2c_adapter *adapter = &radio->i2c_adapter;

	i2c_del_adapter(adapter);
	v4l2_device_unregister(&radio->v4l2_dev);
	kfree(radio->buffer);
	kfree(radio);
}