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
struct dm_thin_device {TYPE_1__* pmd; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
struct TYPE_2__ {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  fail_io; } ;

/* Variables and functions */
 int EINVAL ; 
 int __remove_range (struct dm_thin_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_thin_remove_range(struct dm_thin_device *td,
			 dm_block_t begin, dm_block_t end)
{
	int r = -EINVAL;

	down_write(&td->pmd->root_lock);
	if (!td->pmd->fail_io)
		r = __remove_range(td, begin, end);
	up_write(&td->pmd->root_lock);

	return r;
}