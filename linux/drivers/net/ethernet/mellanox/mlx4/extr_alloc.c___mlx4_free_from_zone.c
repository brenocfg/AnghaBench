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
typedef  scalar_t__ u32 ;
struct mlx4_zone_entry {int /*<<< orphan*/  use_rr; scalar_t__ offset; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_bitmap_free_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mlx4_free_from_zone(struct mlx4_zone_entry *zone, u32 obj,
				  u32 count)
{
	mlx4_bitmap_free_range(zone->bitmap, obj - zone->offset, count, zone->use_rr);
}