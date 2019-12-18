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
struct iavf_virt_mem {int /*<<< orphan*/  va; } ;
struct iavf_hw {int dummy; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;

/* Variables and functions */
 int IAVF_ERR_PARAM ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

enum iavf_status iavf_free_virt_mem_d(struct iavf_hw *hw,
				      struct iavf_virt_mem *mem)
{
	if (!mem)
		return IAVF_ERR_PARAM;

	/* it's ok to kfree a NULL pointer */
	kfree(mem->va);

	return 0;
}