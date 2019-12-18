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
struct md_rdev {scalar_t__ raid_disk; unsigned long long data_offset; unsigned long long new_data_offset; TYPE_1__* mddev; scalar_t__ sectors; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ external; scalar_t__ pers; } ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 scalar_t__ kstrtoull (char const*,int,unsigned long long*) ; 

__attribute__((used)) static ssize_t
offset_store(struct md_rdev *rdev, const char *buf, size_t len)
{
	unsigned long long offset;
	if (kstrtoull(buf, 10, &offset) < 0)
		return -EINVAL;
	if (rdev->mddev->pers && rdev->raid_disk >= 0)
		return -EBUSY;
	if (rdev->sectors && rdev->mddev->external)
		/* Must set offset before size, so overlap checks
		 * can be sane */
		return -EBUSY;
	rdev->data_offset = offset;
	rdev->new_data_offset = offset;
	return len;
}