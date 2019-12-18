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
struct file {struct console_data* private_data; } ;
struct console_data {int /*<<< orphan*/  map_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct console_data*) ; 

__attribute__((used)) static int dpaa2_console_close(struct inode *node, struct file *fp)
{
	struct console_data *cd = fp->private_data;

	iounmap(cd->map_addr);
	kfree(cd);
	return 0;
}