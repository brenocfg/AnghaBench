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
typedef  int /*<<< orphan*/  const u32 ;
struct idt_ntb_dev {int /*<<< orphan*/  gasa_lock; scalar_t__ cfgspc; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 scalar_t__ IDT_NT_GASAADDR ; 
 scalar_t__ IDT_NT_GASADATA ; 
 int /*<<< orphan*/  IDT_REG_ALIGN ; 
 unsigned int const IDT_REG_SW_MAX ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int const,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void idt_sw_write(struct idt_ntb_dev *ndev,
			 const unsigned int reg, const u32 data)
{
	unsigned long irqflags;

	/*
	 * It's obvious bug to request a register exceeding the maximum possible
	 * value as well as to have it unaligned.
	 */
	if (WARN_ON(reg > IDT_REG_SW_MAX || !IS_ALIGNED(reg, IDT_REG_ALIGN)))
		return;

	/* Lock GASA registers operations */
	spin_lock_irqsave(&ndev->gasa_lock, irqflags);
	/* Set the global register address */
	iowrite32((u32)reg, ndev->cfgspc + (ptrdiff_t)IDT_NT_GASAADDR);
	/* Put the new value of the register */
	iowrite32(data, ndev->cfgspc + (ptrdiff_t)IDT_NT_GASADATA);
	/* Unlock GASA registers operations */
	spin_unlock_irqrestore(&ndev->gasa_lock, irqflags);
}