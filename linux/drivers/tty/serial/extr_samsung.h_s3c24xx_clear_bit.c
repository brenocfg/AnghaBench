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
typedef  int u32 ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int rd_regl (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,unsigned int,int) ; 

__attribute__((used)) static inline void s3c24xx_clear_bit(struct uart_port *port, int idx,
				     unsigned int reg)
{
	unsigned long flags;
	u32 val;

	local_irq_save(flags);
	val = rd_regl(port, reg);
	val &= ~(1 << idx);
	wr_regl(port, reg, val);
	local_irq_restore(flags);
}