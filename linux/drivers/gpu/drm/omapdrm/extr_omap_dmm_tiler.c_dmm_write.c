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
struct dmm {scalar_t__ base; int /*<<< orphan*/  wa_lock; scalar_t__ dmm_workaround; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmm_write_wa (struct dmm*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void dmm_write(struct dmm *dmm, u32 val, u32 reg)
{
	if (dmm->dmm_workaround) {
		unsigned long flags;

		spin_lock_irqsave(&dmm->wa_lock, flags);
		dmm_write_wa(dmm, val, reg);
		spin_unlock_irqrestore(&dmm->wa_lock, flags);
	} else {
		writel(val, dmm->base + reg);
	}
}