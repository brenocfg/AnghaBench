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

/* Variables and functions */
 int /*<<< orphan*/ * aoe_debugfs_dir ; 
 int /*<<< orphan*/  buf_pool_cache ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 

void
aoeblk_exit(void)
{
	debugfs_remove_recursive(aoe_debugfs_dir);
	aoe_debugfs_dir = NULL;
	kmem_cache_destroy(buf_pool_cache);
}