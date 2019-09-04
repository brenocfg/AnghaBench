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
struct block_device {int /*<<< orphan*/  bd_inode; } ;
typedef  int sector_t ;

/* Variables and functions */
 int i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline sector_t drbd_get_capacity(struct block_device *bdev)
{
	/* return bdev ? get_capacity(bdev->bd_disk) : 0; */
	return bdev ? i_size_read(bdev->bd_inode) >> 9 : 0;
}