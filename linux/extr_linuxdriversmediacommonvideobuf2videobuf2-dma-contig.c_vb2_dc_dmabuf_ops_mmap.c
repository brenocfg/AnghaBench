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
struct dma_buf {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int vb2_dc_mmap (int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int vb2_dc_dmabuf_ops_mmap(struct dma_buf *dbuf,
	struct vm_area_struct *vma)
{
	return vb2_dc_mmap(dbuf->priv, vma);
}