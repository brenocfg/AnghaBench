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
struct event_device_data {int exist; int /*<<< orphan*/  dev; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hangup_device(struct event_device_data *dev_data)
{
	dev_data->exist = false;
	/* Wake up the waiting processes so they can close. */
	wake_up_interruptible(&dev_data->wq);
	put_device(&dev_data->dev);
}