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
struct iavf_virt_mem {scalar_t__ va; int /*<<< orphan*/  size; } ;
struct iavf_hw {int dummy; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IAVF_ERR_NO_MEMORY ; 
 int IAVF_ERR_PARAM ; 
 scalar_t__ kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum iavf_status iavf_allocate_virt_mem_d(struct iavf_hw *hw,
					  struct iavf_virt_mem *mem, u32 size)
{
	if (!mem)
		return IAVF_ERR_PARAM;

	mem->size = size;
	mem->va = kzalloc(size, GFP_KERNEL);

	if (mem->va)
		return 0;
	else
		return IAVF_ERR_NO_MEMORY;
}