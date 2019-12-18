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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {TYPE_1__* global; } ;
struct etnaviv_iommuv2_context {int* stlb_dma; int* mtlb_cpu; scalar_t__* stlb_cpu; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MMUv2_PTE_EXCEPTION ; 
 int MMUv2_PTE_PRESENT ; 
 int SZ_4K ; 
 scalar_t__ dma_alloc_wc (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset32 (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
etnaviv_iommuv2_ensure_stlb(struct etnaviv_iommuv2_context *v2_context,
			    int stlb)
{
	if (v2_context->stlb_cpu[stlb])
		return 0;

	v2_context->stlb_cpu[stlb] =
			dma_alloc_wc(v2_context->base.global->dev, SZ_4K,
				     &v2_context->stlb_dma[stlb],
				     GFP_KERNEL);

	if (!v2_context->stlb_cpu[stlb])
		return -ENOMEM;

	memset32(v2_context->stlb_cpu[stlb], MMUv2_PTE_EXCEPTION,
		 SZ_4K / sizeof(u32));

	v2_context->mtlb_cpu[stlb] =
			v2_context->stlb_dma[stlb] | MMUv2_PTE_PRESENT;

	return 0;
}