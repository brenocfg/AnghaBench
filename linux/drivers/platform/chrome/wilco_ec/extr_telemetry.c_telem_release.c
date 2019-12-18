#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct telem_session_data {TYPE_1__* dev_data; } ;
struct inode {int dummy; } ;
struct file {struct telem_session_data* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  available; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct telem_session_data*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int telem_release(struct inode *inode, struct file *filp)
{
	struct telem_session_data *sess_data = filp->private_data;

	atomic_set(&sess_data->dev_data->available, 1);
	put_device(&sess_data->dev_data->dev);
	kfree(sess_data);

	return 0;
}