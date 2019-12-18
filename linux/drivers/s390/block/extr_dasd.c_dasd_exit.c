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
 int /*<<< orphan*/ * dasd_debug_area ; 
 int /*<<< orphan*/  dasd_devmap_exit () ; 
 int /*<<< orphan*/  dasd_eer_exit () ; 
 int /*<<< orphan*/  dasd_gendisk_exit () ; 
 int /*<<< orphan*/ * dasd_page_cache ; 
 int /*<<< orphan*/  dasd_proc_exit () ; 
 int /*<<< orphan*/  dasd_statistics_removeroot () ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dasd_exit(void)
{
#ifdef CONFIG_PROC_FS
	dasd_proc_exit();
#endif
	dasd_eer_exit();
	kmem_cache_destroy(dasd_page_cache);
	dasd_page_cache = NULL;
	dasd_gendisk_exit();
	dasd_devmap_exit();
	if (dasd_debug_area != NULL) {
		debug_unregister(dasd_debug_area);
		dasd_debug_area = NULL;
	}
	dasd_statistics_removeroot();
}