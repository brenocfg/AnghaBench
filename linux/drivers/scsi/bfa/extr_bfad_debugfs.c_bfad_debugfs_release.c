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
struct file {struct bfad_debug_info* private_data; } ;
struct bfad_debug_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bfad_debug_info*) ; 

__attribute__((used)) static int
bfad_debugfs_release(struct inode *inode, struct file *file)
{
	struct bfad_debug_info *debug = file->private_data;

	if (!debug)
		return 0;

	file->private_data = NULL;
	kfree(debug);
	return 0;
}