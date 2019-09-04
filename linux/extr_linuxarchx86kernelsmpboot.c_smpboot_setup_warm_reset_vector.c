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

/* Variables and functions */
 int /*<<< orphan*/  CMOS_WRITE (int,int) ; 
 int /*<<< orphan*/  TRAMPOLINE_PHYS_HIGH ; 
 int /*<<< orphan*/  TRAMPOLINE_PHYS_LOW ; 
 scalar_t__ phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void smpboot_setup_warm_reset_vector(unsigned long start_eip)
{
	unsigned long flags;

	spin_lock_irqsave(&rtc_lock, flags);
	CMOS_WRITE(0xa, 0xf);
	spin_unlock_irqrestore(&rtc_lock, flags);
	*((volatile unsigned short *)phys_to_virt(TRAMPOLINE_PHYS_HIGH)) =
							start_eip >> 4;
	*((volatile unsigned short *)phys_to_virt(TRAMPOLINE_PHYS_LOW)) =
							start_eip & 0xf;
}