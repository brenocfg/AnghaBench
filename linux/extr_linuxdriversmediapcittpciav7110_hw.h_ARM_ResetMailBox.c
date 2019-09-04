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
struct av7110 {int /*<<< orphan*/  debilock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBINOSWAP ; 
 int /*<<< orphan*/  IRQ_RX ; 
 int /*<<< orphan*/  av7110_debiread (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av7110_debiwrite (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void ARM_ResetMailBox(struct av7110 *av7110)
{
	unsigned long flags;

	spin_lock_irqsave(&av7110->debilock, flags);
	av7110_debiread(av7110, DEBINOSWAP, IRQ_RX, 2);
	av7110_debiwrite(av7110, DEBINOSWAP, IRQ_RX, 0, 2);
	spin_unlock_irqrestore(&av7110->debilock, flags);
}