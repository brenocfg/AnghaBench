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
struct vm_area_struct {size_t vm_end; size_t vm_start; } ;
struct fastrpc_buf {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; int /*<<< orphan*/  dev; } ;
struct dma_buf {struct fastrpc_buf* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FASTRPC_PHYS (int /*<<< orphan*/ ) ; 
 int dma_mmap_coherent (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int fastrpc_mmap(struct dma_buf *dmabuf,
			struct vm_area_struct *vma)
{
	struct fastrpc_buf *buf = dmabuf->priv;
	size_t size = vma->vm_end - vma->vm_start;

	return dma_mmap_coherent(buf->dev, vma, buf->virt,
				 FASTRPC_PHYS(buf->phys), size);
}