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
struct inode {struct hl_debugfs_entry* i_private; } ;
struct hl_debugfs_entry {TYPE_1__* info_ent; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  show; } ;

/* Variables and functions */
 int single_open (struct file*,int /*<<< orphan*/ ,struct hl_debugfs_entry*) ; 

__attribute__((used)) static int hl_debugfs_open(struct inode *inode, struct file *file)
{
	struct hl_debugfs_entry *node = inode->i_private;

	return single_open(file, node->info_ent->show, node);
}