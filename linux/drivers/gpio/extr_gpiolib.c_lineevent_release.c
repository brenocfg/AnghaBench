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
struct lineevent_state {struct lineevent_state* label; int /*<<< orphan*/  desc; int /*<<< orphan*/  irq; struct gpio_device* gdev; } ;
struct inode {int dummy; } ;
struct gpio_device {int /*<<< orphan*/  dev; } ;
struct file {struct lineevent_state* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct lineevent_state*) ; 
 int /*<<< orphan*/  gpiod_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lineevent_state*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lineevent_release(struct inode *inode, struct file *filep)
{
	struct lineevent_state *le = filep->private_data;
	struct gpio_device *gdev = le->gdev;

	free_irq(le->irq, le);
	gpiod_free(le->desc);
	kfree(le->label);
	kfree(le);
	put_device(&gdev->dev);
	return 0;
}