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
typedef  int uint32_t ;
struct qcm_process_device {void* ib_kaddr; int /*<<< orphan*/  ib_base; } ;
struct kfd_process_device {struct qcm_process_device qpd; } ;

/* Variables and functions */
 int ALLOC_MEM_FLAGS_EXECUTABLE ; 
 int ALLOC_MEM_FLAGS_GTT ; 
 int ALLOC_MEM_FLAGS_NO_SUBSTITUTE ; 
 int ALLOC_MEM_FLAGS_WRITABLE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int kfd_process_alloc_gpuvm (struct kfd_process_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**) ; 

__attribute__((used)) static int kfd_process_device_reserve_ib_mem(struct kfd_process_device *pdd)
{
	struct qcm_process_device *qpd = &pdd->qpd;
	uint32_t flags = ALLOC_MEM_FLAGS_GTT |
			 ALLOC_MEM_FLAGS_NO_SUBSTITUTE |
			 ALLOC_MEM_FLAGS_WRITABLE |
			 ALLOC_MEM_FLAGS_EXECUTABLE;
	void *kaddr;
	int ret;

	if (qpd->ib_kaddr || !qpd->ib_base)
		return 0;

	/* ib_base is only set for dGPU */
	ret = kfd_process_alloc_gpuvm(pdd, qpd->ib_base, PAGE_SIZE, flags,
				      &kaddr);
	if (ret)
		return ret;

	qpd->ib_kaddr = kaddr;

	return 0;
}