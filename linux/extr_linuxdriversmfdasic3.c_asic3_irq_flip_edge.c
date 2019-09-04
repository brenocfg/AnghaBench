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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct asic3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ ASIC3_GPIO_EDGE_TRIGGER ; 
 int asic3_read_register (struct asic3*,scalar_t__) ; 
 int /*<<< orphan*/  asic3_write_register (struct asic3*,scalar_t__,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void asic3_irq_flip_edge(struct asic3 *asic,
				u32 base, int bit)
{
	u16 edge;
	unsigned long flags;

	raw_spin_lock_irqsave(&asic->lock, flags);
	edge = asic3_read_register(asic,
				   base + ASIC3_GPIO_EDGE_TRIGGER);
	edge ^= bit;
	asic3_write_register(asic,
			     base + ASIC3_GPIO_EDGE_TRIGGER, edge);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
}