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
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  phys; scalar_t__ virt; } ;
struct sa_subdev_info {TYPE_1__ map; scalar_t__ mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sa1100_destroy_subdev(struct sa_subdev_info *subdev)
{
	if (subdev->mtd)
		map_destroy(subdev->mtd);
	if (subdev->map.virt)
		iounmap(subdev->map.virt);
	release_mem_region(subdev->map.phys, subdev->map.size);
}