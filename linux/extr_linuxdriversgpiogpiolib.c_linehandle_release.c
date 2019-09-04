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
struct linehandle_state {int numdescs; struct linehandle_state* label; int /*<<< orphan*/ * descs; struct gpio_device* gdev; } ;
struct inode {int dummy; } ;
struct gpio_device {int /*<<< orphan*/  dev; } ;
struct file {struct linehandle_state* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct linehandle_state*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int linehandle_release(struct inode *inode, struct file *filep)
{
	struct linehandle_state *lh = filep->private_data;
	struct gpio_device *gdev = lh->gdev;
	int i;

	for (i = 0; i < lh->numdescs; i++)
		gpiod_free(lh->descs[i]);
	kfree(lh->label);
	kfree(lh);
	put_device(&gdev->dev);
	return 0;
}