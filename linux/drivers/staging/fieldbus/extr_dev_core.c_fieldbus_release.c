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
struct file {struct fb_open_file* private_data; } ;
struct fb_open_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fb_open_file*) ; 

__attribute__((used)) static int fieldbus_release(struct inode *node, struct file *filp)
{
	struct fb_open_file *of = filp->private_data;

	kfree(of);
	return 0;
}