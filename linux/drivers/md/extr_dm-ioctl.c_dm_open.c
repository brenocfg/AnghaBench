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
struct inode {int dummy; } ;
struct file {struct dm_file* private_data; } ;
struct dm_file {int /*<<< orphan*/  global_event_nr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_global_event_nr ; 
 struct dm_file* kmalloc (int,int /*<<< orphan*/ ) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dm_open(struct inode *inode, struct file *filp)
{
	int r;
	struct dm_file *priv;

	r = nonseekable_open(inode, filp);
	if (unlikely(r))
		return r;

	priv = filp->private_data = kmalloc(sizeof(struct dm_file), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->global_event_nr = atomic_read(&dm_global_event_nr);

	return 0;
}