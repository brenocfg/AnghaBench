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
struct vsoc_device_region {int /*<<< orphan*/  device_name; scalar_t__ region_begin_offset; } ;
struct fd_scoped_permission {int owned_value; scalar_t__ owner_offset; int /*<<< orphan*/  end_offset; int /*<<< orphan*/  begin_offset; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSOC_REGION_FREE ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ shm_off_to_virtual_addr (scalar_t__) ; 
 TYPE_2__ vsoc_dev ; 

__attribute__((used)) static void
do_destroy_fd_scoped_permission(struct vsoc_device_region *owner_region_p,
				struct fd_scoped_permission *perm)
{
	atomic_t *owner_ptr = NULL;
	int prev = 0;

	if (!perm)
		return;
	owner_ptr = (atomic_t *)shm_off_to_virtual_addr
		(owner_region_p->region_begin_offset + perm->owner_offset);
	prev = atomic_xchg(owner_ptr, VSOC_REGION_FREE);
	if (prev != perm->owned_value)
		dev_err(&vsoc_dev.dev->dev,
			"%x-%x: owner (%s) %x: expected to be %x was %x",
			perm->begin_offset, perm->end_offset,
			owner_region_p->device_name, perm->owner_offset,
			perm->owned_value, prev);
}