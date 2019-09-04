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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct vmw_private {int /*<<< orphan*/  cursor_lock; int /*<<< orphan*/ * mmio_virt; } ;

/* Variables and functions */
 int SVGA_FIFO_CURSOR_COUNT ; 
 int SVGA_FIFO_CURSOR_ON ; 
 int SVGA_FIFO_CURSOR_X ; 
 int SVGA_FIFO_CURSOR_Y ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vmw_mmio_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_mmio_write (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_cursor_update_position(struct vmw_private *dev_priv,
				       bool show, int x, int y)
{
	u32 *fifo_mem = dev_priv->mmio_virt;
	uint32_t count;

	spin_lock(&dev_priv->cursor_lock);
	vmw_mmio_write(show ? 1 : 0, fifo_mem + SVGA_FIFO_CURSOR_ON);
	vmw_mmio_write(x, fifo_mem + SVGA_FIFO_CURSOR_X);
	vmw_mmio_write(y, fifo_mem + SVGA_FIFO_CURSOR_Y);
	count = vmw_mmio_read(fifo_mem + SVGA_FIFO_CURSOR_COUNT);
	vmw_mmio_write(++count, fifo_mem + SVGA_FIFO_CURSOR_COUNT);
	spin_unlock(&dev_priv->cursor_lock);
}