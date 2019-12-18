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
struct joydev_client {struct joydev* joydev; } ;
struct joydev {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct joydev_client* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  joydev_close_device (struct joydev*) ; 
 int /*<<< orphan*/  joydev_detach_client (struct joydev*,struct joydev_client*) ; 
 int /*<<< orphan*/  kfree (struct joydev_client*) ; 

__attribute__((used)) static int joydev_release(struct inode *inode, struct file *file)
{
	struct joydev_client *client = file->private_data;
	struct joydev *joydev = client->joydev;

	joydev_detach_client(joydev, client);
	kfree(client);

	joydev_close_device(joydev);

	return 0;
}