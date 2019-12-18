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
struct TYPE_4__ {int /*<<< orphan*/  domain; } ;
struct dma_domain {struct dma_map_ops* dma_ops; int /*<<< orphan*/  domain_nr; } ;
struct dma_map_ops {int dummy; } ;
struct vmd_dev {TYPE_2__ sysdata; struct dma_domain dma_domain; struct dma_map_ops dma_ops; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_VMD_DMA_OPS (struct dma_map_ops const*,struct dma_map_ops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_dma_domain (struct dma_domain*) ; 
 int /*<<< orphan*/  alloc ; 
 int /*<<< orphan*/  dma_supported ; 
 int /*<<< orphan*/  free ; 
 struct dma_map_ops* get_dma_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_required_mask ; 
 int /*<<< orphan*/  get_sgtable ; 
 int /*<<< orphan*/  map_page ; 
 int /*<<< orphan*/  map_sg ; 
 int /*<<< orphan*/  mmap ; 
 int /*<<< orphan*/  sync_sg_for_cpu ; 
 int /*<<< orphan*/  sync_sg_for_device ; 
 int /*<<< orphan*/  sync_single_for_cpu ; 
 int /*<<< orphan*/  sync_single_for_device ; 
 int /*<<< orphan*/  unmap_page ; 
 int /*<<< orphan*/  unmap_sg ; 

__attribute__((used)) static void vmd_setup_dma_ops(struct vmd_dev *vmd)
{
	const struct dma_map_ops *source = get_dma_ops(&vmd->dev->dev);
	struct dma_map_ops *dest = &vmd->dma_ops;
	struct dma_domain *domain = &vmd->dma_domain;

	domain->domain_nr = vmd->sysdata.domain;
	domain->dma_ops = dest;

	if (!source)
		return;
	ASSIGN_VMD_DMA_OPS(source, dest, alloc);
	ASSIGN_VMD_DMA_OPS(source, dest, free);
	ASSIGN_VMD_DMA_OPS(source, dest, mmap);
	ASSIGN_VMD_DMA_OPS(source, dest, get_sgtable);
	ASSIGN_VMD_DMA_OPS(source, dest, map_page);
	ASSIGN_VMD_DMA_OPS(source, dest, unmap_page);
	ASSIGN_VMD_DMA_OPS(source, dest, map_sg);
	ASSIGN_VMD_DMA_OPS(source, dest, unmap_sg);
	ASSIGN_VMD_DMA_OPS(source, dest, sync_single_for_cpu);
	ASSIGN_VMD_DMA_OPS(source, dest, sync_single_for_device);
	ASSIGN_VMD_DMA_OPS(source, dest, sync_sg_for_cpu);
	ASSIGN_VMD_DMA_OPS(source, dest, sync_sg_for_device);
	ASSIGN_VMD_DMA_OPS(source, dest, dma_supported);
	ASSIGN_VMD_DMA_OPS(source, dest, get_required_mask);
	add_dma_domain(domain);
}