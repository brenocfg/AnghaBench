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
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int MAX_PINS ; 
 unsigned int iminor (struct inode*) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  scx200_gpio_ops ; 

__attribute__((used)) static int scx200_gpio_open(struct inode *inode, struct file *file)
{
	unsigned m = iminor(inode);
	file->private_data = &scx200_gpio_ops;

	if (m >= MAX_PINS)
		return -EINVAL;
	return nonseekable_open(inode, file);
}