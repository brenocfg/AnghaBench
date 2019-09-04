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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct fpga_region {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpga_region_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fpga_region*) ; 

void fpga_region_free(struct fpga_region *region)
{
	ida_simple_remove(&fpga_region_ida, region->dev.id);
	kfree(region);
}