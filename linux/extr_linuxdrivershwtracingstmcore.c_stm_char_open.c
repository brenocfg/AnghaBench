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
struct stm_file {TYPE_1__* stm; int /*<<< orphan*/  output; } ;
struct inode {int dummy; } ;
struct file {struct stm_file* private_data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ) ; 
 unsigned int imajor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct stm_file*) ; 
 struct stm_file* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  major_match ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  stm_class ; 
 int /*<<< orphan*/  stm_output_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_stm_device (struct device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm_char_open(struct inode *inode, struct file *file)
{
	struct stm_file *stmf;
	struct device *dev;
	unsigned int major = imajor(inode);
	int err = -ENOMEM;

	dev = class_find_device(&stm_class, NULL, &major, major_match);
	if (!dev)
		return -ENODEV;

	stmf = kzalloc(sizeof(*stmf), GFP_KERNEL);
	if (!stmf)
		goto err_put_device;

	err = -ENODEV;
	stm_output_init(&stmf->output);
	stmf->stm = to_stm_device(dev);

	if (!try_module_get(stmf->stm->owner))
		goto err_free;

	file->private_data = stmf;

	return nonseekable_open(inode, file);

err_free:
	kfree(stmf);
err_put_device:
	/* matches class_find_device() above */
	put_device(dev);

	return err;
}