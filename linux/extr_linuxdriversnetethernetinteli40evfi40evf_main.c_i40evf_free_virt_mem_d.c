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
struct i40e_virt_mem {int /*<<< orphan*/  va; } ;
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

i40e_status i40evf_free_virt_mem_d(struct i40e_hw *hw,
				   struct i40e_virt_mem *mem)
{
	if (!mem)
		return I40E_ERR_PARAM;

	/* it's ok to kfree a NULL pointer */
	kfree(mem->va);

	return 0;
}