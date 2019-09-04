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
struct vm_area_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_buf; } ;
struct etnaviv_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int dma_buf_mmap (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int etnaviv_gem_prime_mmap_obj(struct etnaviv_gem_object *etnaviv_obj,
		struct vm_area_struct *vma)
{
	return dma_buf_mmap(etnaviv_obj->base.dma_buf, vma, 0);
}