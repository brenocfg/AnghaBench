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
struct page {int dummy; } ;
struct arm_dma_alloc_args {int /*<<< orphan*/  gfp; int /*<<< orphan*/  coherent_flag; int /*<<< orphan*/  want_vaddr; int /*<<< orphan*/  caller; int /*<<< orphan*/  prot; int /*<<< orphan*/  size; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* __alloc_from_contiguous (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *cma_allocator_alloc(struct arm_dma_alloc_args *args,
				 struct page **ret_page)
{
	return __alloc_from_contiguous(args->dev, args->size, args->prot,
				       ret_page, args->caller,
				       args->want_vaddr, args->coherent_flag,
				       args->gfp);
}