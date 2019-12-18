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
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 
 int /*<<< orphan*/  hga_reg_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_hga_w (unsigned int,int) ; 

__attribute__((used)) static void hga_pan(unsigned int xoffset, unsigned int yoffset)
{
	unsigned int base;
	unsigned long flags;
	
	base = (yoffset / 8) * 90 + xoffset;
	spin_lock_irqsave(&hga_reg_lock, flags);
	write_hga_w(base, 0x0c);	/* start address */
	spin_unlock_irqrestore(&hga_reg_lock, flags);
	DPRINTK("hga_pan: base:%d\n", base);
}