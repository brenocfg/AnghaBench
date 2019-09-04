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
struct gnss_device {int /*<<< orphan*/  id; int /*<<< orphan*/  read_fifo; struct gnss_device* write_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnss_minors ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gnss_device*) ; 
 struct gnss_device* to_gnss_device (struct device*) ; 

__attribute__((used)) static void gnss_device_release(struct device *dev)
{
	struct gnss_device *gdev = to_gnss_device(dev);

	kfree(gdev->write_buf);
	kfifo_free(&gdev->read_fifo);
	ida_simple_remove(&gnss_minors, gdev->id);
	kfree(gdev);
}