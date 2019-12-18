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
struct shark_device {struct shark_device* transfer_buffer; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct shark_device*) ; 
 struct shark_device* v4l2_dev_to_shark (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_shark_release(struct v4l2_device *v4l2_dev)
{
	struct shark_device *shark = v4l2_dev_to_shark(v4l2_dev);

	v4l2_device_unregister(&shark->v4l2_dev);
	kfree(shark->transfer_buffer);
	kfree(shark);
}