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
typedef  int /*<<< orphan*/  u8 ;
typedef  long u32 ;
struct i40iw_dma_mem {long size; scalar_t__ va; scalar_t__ pa; } ;
struct TYPE_4__ {scalar_t__ va; scalar_t__ pa; } ;
struct TYPE_3__ {scalar_t__ va; scalar_t__ size; } ;
struct i40iw_device {TYPE_2__ obj_next; TYPE_1__ obj_mem; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,long) ; 
 int I40IW_ERR_NO_MEMORY ; 

enum i40iw_status_code i40iw_obj_aligned_mem(struct i40iw_device *iwdev,
					     struct i40iw_dma_mem *memptr,
					     u32 size,
					     u32 mask)
{
	unsigned long va, newva;
	unsigned long extra;

	va = (unsigned long)iwdev->obj_next.va;
	newva = va;
	if (mask)
		newva = ALIGN(va, (mask + 1));
	extra = newva - va;
	memptr->va = (u8 *)va + extra;
	memptr->pa = iwdev->obj_next.pa + extra;
	memptr->size = size;
	if ((memptr->va + size) > (iwdev->obj_mem.va + iwdev->obj_mem.size))
		return I40IW_ERR_NO_MEMORY;

	iwdev->obj_next.va = memptr->va + size;
	iwdev->obj_next.pa = memptr->pa + size;
	return 0;
}