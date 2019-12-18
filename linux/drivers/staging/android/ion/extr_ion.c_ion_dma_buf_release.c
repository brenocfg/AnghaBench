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
struct ion_buffer {int dummy; } ;
struct dma_buf {struct ion_buffer* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ion_buffer_destroy (struct ion_buffer*) ; 

__attribute__((used)) static void ion_dma_buf_release(struct dma_buf *dmabuf)
{
	struct ion_buffer *buffer = dmabuf->priv;

	_ion_buffer_destroy(buffer);
}