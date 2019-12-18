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
struct privcmd_buf_private {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct inode {int dummy; } ;
struct file {struct privcmd_buf_private* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct privcmd_buf_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int privcmd_buf_open(struct inode *ino, struct file *file)
{
	struct privcmd_buf_private *file_priv;

	file_priv = kzalloc(sizeof(*file_priv), GFP_KERNEL);
	if (!file_priv)
		return -ENOMEM;

	mutex_init(&file_priv->lock);
	INIT_LIST_HEAD(&file_priv->list);

	file->private_data = file_priv;

	return 0;
}