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
 int SECTOR_SHIFT ; 
 int i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline sector_t get_dev_size(struct block_device *bdev)
{
	return i_size_read(bdev->bd_inode) >> SECTOR_SHIFT;
}