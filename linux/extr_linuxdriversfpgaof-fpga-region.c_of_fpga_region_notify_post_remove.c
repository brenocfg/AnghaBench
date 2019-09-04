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
struct of_overlay_notify_data {int dummy; } ;
struct fpga_region {int /*<<< orphan*/ * info; int /*<<< orphan*/  bridge_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpga_bridges_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpga_bridges_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpga_image_info_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void of_fpga_region_notify_post_remove(struct fpga_region *region,
					      struct of_overlay_notify_data *nd)
{
	fpga_bridges_disable(&region->bridge_list);
	fpga_bridges_put(&region->bridge_list);
	fpga_image_info_free(region->info);
	region->info = NULL;
}