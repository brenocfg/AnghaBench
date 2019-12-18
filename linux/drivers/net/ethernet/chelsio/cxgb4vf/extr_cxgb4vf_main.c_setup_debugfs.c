#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct adapter {int /*<<< orphan*/  debugfs_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  fops; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* debugfs_files ; 

__attribute__((used)) static int setup_debugfs(struct adapter *adapter)
{
	int i;

	BUG_ON(IS_ERR_OR_NULL(adapter->debugfs_root));

	/*
	 * Debugfs support is best effort.
	 */
	for (i = 0; i < ARRAY_SIZE(debugfs_files); i++)
		debugfs_create_file(debugfs_files[i].name,
				    debugfs_files[i].mode,
				    adapter->debugfs_root, (void *)adapter,
				    debugfs_files[i].fops);

	return 0;
}