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
struct adapter {int /*<<< orphan*/  debugfs_root; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_setup_debugfs (struct adapter*) ; 

__attribute__((used)) static int setup_debugfs(struct adapter *adap)
{
	if (IS_ERR_OR_NULL(adap->debugfs_root))
		return -1;

#ifdef CONFIG_DEBUG_FS
	t4_setup_debugfs(adap);
#endif
	return 0;
}