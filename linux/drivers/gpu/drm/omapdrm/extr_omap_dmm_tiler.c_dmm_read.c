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
 scalar_t__ dmm_read_wa (struct dmm*,scalar_t__) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 dmm_read(struct dmm *dmm, u32 reg)
{
	if (dmm->dmm_workaround) {
		u32 v;
		unsigned long flags;

		spin_lock_irqsave(&dmm->wa_lock, flags);
		v = dmm_read_wa(dmm, reg);
		spin_unlock_irqrestore(&dmm->wa_lock, flags);

		return v;
	} else {
		return readl(dmm->base + reg);
	}
}