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
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int matroxfb_DAC_in (struct matrox_fb_info*,int) ; 
 int /*<<< orphan*/  matroxfb_DAC_lock_irqsave (unsigned long) ; 
 int /*<<< orphan*/  matroxfb_DAC_out (struct matrox_fb_info*,int,int) ; 
 int /*<<< orphan*/  matroxfb_DAC_unlock_irqrestore (unsigned long) ; 

__attribute__((used)) static int cve2_get_reg(struct matrox_fb_info *minfo, int reg)
{
	unsigned long flags;
	int val;
	
	matroxfb_DAC_lock_irqsave(flags);
	matroxfb_DAC_out(minfo, 0x87, reg);
	val = matroxfb_DAC_in(minfo, 0x88);
	matroxfb_DAC_unlock_irqrestore(flags);
	return val;
}