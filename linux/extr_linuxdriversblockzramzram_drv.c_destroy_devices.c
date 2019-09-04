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
 int /*<<< orphan*/  CPUHP_ZCOMP_PREPARE ; 
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuhp_remove_multi_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_blkdev (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zram_control_class ; 
 int /*<<< orphan*/  zram_debugfs_destroy () ; 
 int /*<<< orphan*/  zram_index_idr ; 
 int /*<<< orphan*/  zram_major ; 
 int /*<<< orphan*/  zram_remove_cb ; 

__attribute__((used)) static void destroy_devices(void)
{
	class_unregister(&zram_control_class);
	idr_for_each(&zram_index_idr, &zram_remove_cb, NULL);
	zram_debugfs_destroy();
	idr_destroy(&zram_index_idr);
	unregister_blkdev(zram_major, "zram");
	cpuhp_remove_multi_state(CPUHP_ZCOMP_PREPARE);
}