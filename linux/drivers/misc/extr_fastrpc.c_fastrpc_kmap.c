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
struct fastrpc_buf {void* virt; } ;
struct dma_buf {struct fastrpc_buf* priv; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 

__attribute__((used)) static void *fastrpc_kmap(struct dma_buf *dmabuf, unsigned long pgnum)
{
	struct fastrpc_buf *buf = dmabuf->priv;

	return buf->virt ? buf->virt + pgnum * PAGE_SIZE : NULL;
}