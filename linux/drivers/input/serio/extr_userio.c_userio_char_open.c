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
struct userio_device {TYPE_1__* serio; int /*<<< orphan*/  waitq; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  mutex; } ;
struct serio {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct userio_device* private_data; } ;
struct TYPE_2__ {struct userio_device* port_data; int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct userio_device*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userio_device_write ; 

__attribute__((used)) static int userio_char_open(struct inode *inode, struct file *file)
{
	struct userio_device *userio;

	userio = kzalloc(sizeof(struct userio_device), GFP_KERNEL);
	if (!userio)
		return -ENOMEM;

	mutex_init(&userio->mutex);
	spin_lock_init(&userio->buf_lock);
	init_waitqueue_head(&userio->waitq);

	userio->serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!userio->serio) {
		kfree(userio);
		return -ENOMEM;
	}

	userio->serio->write = userio_device_write;
	userio->serio->port_data = userio;

	file->private_data = userio;

	return 0;
}