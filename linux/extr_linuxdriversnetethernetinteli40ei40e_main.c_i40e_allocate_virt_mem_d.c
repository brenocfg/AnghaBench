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
typedef  int /*<<< orphan*/  u32 ;
struct i40e_virt_mem {int /*<<< orphan*/  va; int /*<<< orphan*/  size; } ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int i40e_allocate_virt_mem_d(struct i40e_hw *hw, struct i40e_virt_mem *mem,
			     u32 size)
{
	mem->size = size;
	mem->va = kzalloc(size, GFP_KERNEL);

	if (!mem->va)
		return -ENOMEM;

	return 0;
}