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
 int HGA_MODE_GRAPHICS ; 
 int /*<<< orphan*/  HGA_MODE_PORT ; 
 int HGA_MODE_VIDEO_EN ; 
 int /*<<< orphan*/  hga_reg_lock ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hga_blank(int blank_mode)
{
	unsigned long flags;

	spin_lock_irqsave(&hga_reg_lock, flags);
	if (blank_mode) {
		outb_p(0x00, HGA_MODE_PORT);	/* disable video */
	} else {
		outb_p(HGA_MODE_VIDEO_EN | HGA_MODE_GRAPHICS, HGA_MODE_PORT);
	}
	spin_unlock_irqrestore(&hga_reg_lock, flags);
}