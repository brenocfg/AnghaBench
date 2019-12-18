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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct idt_ntb_dev {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int idt_nt_read (struct idt_ntb_dev*,unsigned int) ; 
 int /*<<< orphan*/  idt_nt_write (struct idt_ntb_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void idt_reg_clear_bits(struct idt_ntb_dev *ndev,
				     unsigned int reg, spinlock_t *reg_lock,
				     u64 clear_bits)
{
	unsigned long irqflags;
	u32 data;

	/* Lock access to the register unless the change is written back */
	spin_lock_irqsave(reg_lock, irqflags);
	data = idt_nt_read(ndev, reg) & ~(u32)clear_bits;
	idt_nt_write(ndev, reg, data);
	/* Unlock the register */
	spin_unlock_irqrestore(reg_lock, irqflags);
}