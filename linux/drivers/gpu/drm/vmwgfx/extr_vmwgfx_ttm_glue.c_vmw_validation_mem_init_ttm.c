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
struct vmw_validation_mem {size_t gran; int /*<<< orphan*/  unreserve_mem; int /*<<< orphan*/  reserve_mem; } ;
struct vmw_private {struct vmw_validation_mem vvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_vmt_reserve ; 
 int /*<<< orphan*/  vmw_vmt_unreserve ; 

void vmw_validation_mem_init_ttm(struct vmw_private *dev_priv, size_t gran)
{
	struct vmw_validation_mem *vvm = &dev_priv->vvm;

	vvm->reserve_mem = vmw_vmt_reserve;
	vvm->unreserve_mem = vmw_vmt_unreserve;
	vvm->gran = gran;
}