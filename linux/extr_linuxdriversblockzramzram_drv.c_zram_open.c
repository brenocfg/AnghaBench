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
struct zram {scalar_t__ claim; } ;
struct block_device {TYPE_1__* bd_disk; int /*<<< orphan*/  bd_mutex; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct zram* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zram_open(struct block_device *bdev, fmode_t mode)
{
	int ret = 0;
	struct zram *zram;

	WARN_ON(!mutex_is_locked(&bdev->bd_mutex));

	zram = bdev->bd_disk->private_data;
	/* zram was claimed to reset so open request fails */
	if (zram->claim)
		ret = -EBUSY;

	return ret;
}