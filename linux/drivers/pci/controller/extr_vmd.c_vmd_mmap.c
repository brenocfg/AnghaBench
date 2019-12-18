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
struct vm_area_struct {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int dma_mmap_attrs (int /*<<< orphan*/ ,struct vm_area_struct*,void*,int /*<<< orphan*/ ,size_t,unsigned long) ; 
 int /*<<< orphan*/  to_vmd_dev (struct device*) ; 

__attribute__((used)) static int vmd_mmap(struct device *dev, struct vm_area_struct *vma,
		    void *cpu_addr, dma_addr_t addr, size_t size,
		    unsigned long attrs)
{
	return dma_mmap_attrs(to_vmd_dev(dev), vma, cpu_addr, addr, size,
			attrs);
}