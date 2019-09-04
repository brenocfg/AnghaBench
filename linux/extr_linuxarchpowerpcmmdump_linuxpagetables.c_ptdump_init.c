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
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  build_pgtable_complete_mask () ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  populate_markers () ; 
 int /*<<< orphan*/  ptdump_fops ; 

__attribute__((used)) static int ptdump_init(void)
{
	struct dentry *debugfs_file;

	populate_markers();
	build_pgtable_complete_mask();
	debugfs_file = debugfs_create_file("kernel_page_tables", 0400, NULL,
			NULL, &ptdump_fops);
	return debugfs_file ? 0 : -ENOMEM;
}