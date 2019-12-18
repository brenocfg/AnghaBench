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
typedef  scalar_t__ u32 ;
struct esas2r_mem_desc {scalar_t__ size; int /*<<< orphan*/ * virt_addr; scalar_t__ phys_addr; int /*<<< orphan*/ * esas2r_data; scalar_t__ esas2r_param; } ;
struct esas2r_adapter {TYPE_1__* pcid; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ESAS2R_LOG_CRIT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * PTR_ALIGN (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool esas2r_initmem_alloc(struct esas2r_adapter *a,
				 struct esas2r_mem_desc *mem_desc,
				 u32 align)
{
	mem_desc->esas2r_param = mem_desc->size + align;
	mem_desc->virt_addr = NULL;
	mem_desc->phys_addr = 0;
	mem_desc->esas2r_data = dma_alloc_coherent(&a->pcid->dev,
						   (size_t)mem_desc->
						   esas2r_param,
						   (dma_addr_t *)&mem_desc->
						   phys_addr,
						   GFP_KERNEL);

	if (mem_desc->esas2r_data == NULL) {
		esas2r_log(ESAS2R_LOG_CRIT,
			   "failed to allocate %lu bytes of consistent memory!",
			   (long
			    unsigned
			    int)mem_desc->esas2r_param);
		return false;
	}

	mem_desc->virt_addr = PTR_ALIGN(mem_desc->esas2r_data, align);
	mem_desc->phys_addr = ALIGN(mem_desc->phys_addr, align);
	memset(mem_desc->virt_addr, 0, mem_desc->size);
	return true;
}