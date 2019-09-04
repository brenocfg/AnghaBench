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
struct denali_nand_info {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static uint32_t denali_check_irq(struct denali_nand_info *denali)
{
	unsigned long flags;
	uint32_t irq_status;

	spin_lock_irqsave(&denali->irq_lock, flags);
	irq_status = denali->irq_status;
	spin_unlock_irqrestore(&denali->irq_lock, flags);

	return irq_status;
}