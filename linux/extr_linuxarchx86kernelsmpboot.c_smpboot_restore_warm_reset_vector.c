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

/* Variables and functions */
 int /*<<< orphan*/  CMOS_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRAMPOLINE_PHYS_LOW ; 
 scalar_t__ phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void smpboot_restore_warm_reset_vector(void)
{
	unsigned long flags;

	/*
	 * Paranoid:  Set warm reset code and vector here back
	 * to default values.
	 */
	spin_lock_irqsave(&rtc_lock, flags);
	CMOS_WRITE(0, 0xf);
	spin_unlock_irqrestore(&rtc_lock, flags);

	*((volatile u32 *)phys_to_virt(TRAMPOLINE_PHYS_LOW)) = 0;
}