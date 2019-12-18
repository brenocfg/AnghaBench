#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct log_writes_c {TYPE_2__* logdev; } ;
typedef  int sector_t ;
struct TYPE_4__ {TYPE_1__* bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline sector_t logdev_last_sector(struct log_writes_c *lc)
{
	return i_size_read(lc->logdev->bdev->bd_inode) >> SECTOR_SHIFT;
}