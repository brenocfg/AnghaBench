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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct vmw_private {int /*<<< orphan*/ * mmio_virt; } ;

/* Variables and functions */
 int SVGA_FIFO_MAX ; 
 int SVGA_FIFO_MIN ; 
 int SVGA_FIFO_NEXT_CMD ; 
 int SVGA_FIFO_STOP ; 
 scalar_t__ vmw_mmio_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vmw_fifo_is_full(struct vmw_private *dev_priv, uint32_t bytes)
{
	u32  *fifo_mem = dev_priv->mmio_virt;
	uint32_t max = vmw_mmio_read(fifo_mem + SVGA_FIFO_MAX);
	uint32_t next_cmd = vmw_mmio_read(fifo_mem + SVGA_FIFO_NEXT_CMD);
	uint32_t min = vmw_mmio_read(fifo_mem + SVGA_FIFO_MIN);
	uint32_t stop = vmw_mmio_read(fifo_mem + SVGA_FIFO_STOP);

	return ((max - next_cmd) + (stop - min) <= bytes);
}