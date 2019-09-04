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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  sm_shmem_in_base; TYPE_1__* chip; } ;
struct TYPE_3__ {unsigned int shmem_size; int /*<<< orphan*/  cmd_shmem_in_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 TYPE_2__ fw ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned int) ; 
 scalar_t__ meson_sm_call (unsigned int,int*,int,int,int,int,int) ; 

int meson_sm_call_write(void *buffer, unsigned int size, unsigned int cmd_index,
			u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4)
{
	u32 written;

	if (!fw.chip)
		return -ENOENT;

	if (size > fw.chip->shmem_size)
		return -EINVAL;

	if (!fw.chip->cmd_shmem_in_base)
		return -EINVAL;

	memcpy(fw.sm_shmem_in_base, buffer, size);

	if (meson_sm_call(cmd_index, &written, arg0, arg1, arg2, arg3, arg4) < 0)
		return -EINVAL;

	if (!written)
		return -EINVAL;

	return written;
}