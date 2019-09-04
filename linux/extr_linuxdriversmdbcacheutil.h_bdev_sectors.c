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
struct block_device {TYPE_1__* bd_inode; } ;
typedef  int sector_t ;
struct TYPE_2__ {int i_size; } ;

/* Variables and functions */

__attribute__((used)) static inline sector_t bdev_sectors(struct block_device *bdev)
{
	return bdev->bd_inode->i_size >> 9;
}