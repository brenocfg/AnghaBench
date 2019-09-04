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
struct qcom_scm_vmperm {int vmid; int perm; } ;
struct qcom_scm_mem_map_info {void* mem_size; void* mem_addr; } ;
struct qcom_scm_current_perm_info {scalar_t__ ctx_size; scalar_t__ ctx; void* perm; void* vmid; } ;
typedef  size_t phys_addr_t ;
typedef  void* __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int BIT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SZ_64 ; 
 int __qcom_scm_assign_mem (int /*<<< orphan*/ ,size_t,size_t,size_t,size_t,size_t,size_t) ; 
 TYPE_1__* __scm ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,void*,size_t) ; 
 int ffs (unsigned int) ; 
 int hweight_long (unsigned int) ; 

int qcom_scm_assign_mem(phys_addr_t mem_addr, size_t mem_sz,
			unsigned int *srcvm,
			struct qcom_scm_vmperm *newvm, int dest_cnt)
{
	struct qcom_scm_current_perm_info *destvm;
	struct qcom_scm_mem_map_info *mem_to_map;
	phys_addr_t mem_to_map_phys;
	phys_addr_t dest_phys;
	phys_addr_t ptr_phys;
	size_t mem_to_map_sz;
	size_t dest_sz;
	size_t src_sz;
	size_t ptr_sz;
	int next_vm;
	__le32 *src;
	void *ptr;
	int ret;
	int len;
	int i;

	src_sz = hweight_long(*srcvm) * sizeof(*src);
	mem_to_map_sz = sizeof(*mem_to_map);
	dest_sz = dest_cnt * sizeof(*destvm);
	ptr_sz = ALIGN(src_sz, SZ_64) + ALIGN(mem_to_map_sz, SZ_64) +
			ALIGN(dest_sz, SZ_64);

	ptr = dma_alloc_coherent(__scm->dev, ptr_sz, &ptr_phys, GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	/* Fill source vmid detail */
	src = ptr;
	len = hweight_long(*srcvm);
	for (i = 0; i < len; i++) {
		src[i] = cpu_to_le32(ffs(*srcvm) - 1);
		*srcvm ^= 1 << (ffs(*srcvm) - 1);
	}

	/* Fill details of mem buff to map */
	mem_to_map = ptr + ALIGN(src_sz, SZ_64);
	mem_to_map_phys = ptr_phys + ALIGN(src_sz, SZ_64);
	mem_to_map[0].mem_addr = cpu_to_le64(mem_addr);
	mem_to_map[0].mem_size = cpu_to_le64(mem_sz);

	next_vm = 0;
	/* Fill details of next vmid detail */
	destvm = ptr + ALIGN(mem_to_map_sz, SZ_64) + ALIGN(src_sz, SZ_64);
	dest_phys = ptr_phys + ALIGN(mem_to_map_sz, SZ_64) + ALIGN(src_sz, SZ_64);
	for (i = 0; i < dest_cnt; i++) {
		destvm[i].vmid = cpu_to_le32(newvm[i].vmid);
		destvm[i].perm = cpu_to_le32(newvm[i].perm);
		destvm[i].ctx = 0;
		destvm[i].ctx_size = 0;
		next_vm |= BIT(newvm[i].vmid);
	}

	ret = __qcom_scm_assign_mem(__scm->dev, mem_to_map_phys, mem_to_map_sz,
				    ptr_phys, src_sz, dest_phys, dest_sz);
	dma_free_coherent(__scm->dev, ALIGN(ptr_sz, SZ_64), ptr, ptr_phys);
	if (ret) {
		dev_err(__scm->dev,
			"Assign memory protection call failed %d.\n", ret);
		return -EINVAL;
	}

	*srcvm = next_vm;
	return 0;
}