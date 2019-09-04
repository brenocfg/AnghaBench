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
struct vb2_plane {scalar_t__ dbuf_mapped; int /*<<< orphan*/ * dbuf; int /*<<< orphan*/ * mem_priv; } ;
struct vb2_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_void_memop (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  detach_dmabuf ; 
 int /*<<< orphan*/  dma_buf_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_dmabuf ; 

__attribute__((used)) static void __vb2_plane_dmabuf_put(struct vb2_buffer *vb, struct vb2_plane *p)
{
	if (!p->mem_priv)
		return;

	if (p->dbuf_mapped)
		call_void_memop(vb, unmap_dmabuf, p->mem_priv);

	call_void_memop(vb, detach_dmabuf, p->mem_priv);
	dma_buf_put(p->dbuf);
	p->mem_priv = NULL;
	p->dbuf = NULL;
	p->dbuf_mapped = 0;
}