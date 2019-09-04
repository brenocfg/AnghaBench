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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct vmw_private {int /*<<< orphan*/ * mmio_virt; } ;

/* Variables and functions */
 int SVGA_FIFO_BUSY ; 
 int /*<<< orphan*/  SVGA_REG_SYNC ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  vmw_write (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vmw_fifo_ping_host(struct vmw_private *dev_priv, uint32_t reason)
{
	u32 *fifo_mem = dev_priv->mmio_virt;

	preempt_disable();
	if (cmpxchg(fifo_mem + SVGA_FIFO_BUSY, 0, 1) == 0)
		vmw_write(dev_priv, SVGA_REG_SYNC, reason);
	preempt_enable();
}