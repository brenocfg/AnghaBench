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
struct block_device {TYPE_2__* bd_contains; } ;
struct TYPE_4__ {TYPE_1__* bd_disk; } ;
struct TYPE_3__ {int /*<<< orphan*/  sync_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void md_sync_acct(struct block_device *bdev, unsigned long nr_sectors)
{
	atomic_add(nr_sectors, &bdev->bd_contains->bd_disk->sync_io);
}