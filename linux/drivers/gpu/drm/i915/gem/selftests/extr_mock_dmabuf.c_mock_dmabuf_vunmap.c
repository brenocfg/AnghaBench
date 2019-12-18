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
struct mock_dmabuf {int /*<<< orphan*/  npages; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 struct mock_dmabuf* to_mock (struct dma_buf*) ; 
 int /*<<< orphan*/  vm_unmap_ram (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mock_dmabuf_vunmap(struct dma_buf *dma_buf, void *vaddr)
{
	struct mock_dmabuf *mock = to_mock(dma_buf);

	vm_unmap_ram(vaddr, mock->npages);
}