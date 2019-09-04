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
struct tea5764_regs {int tnctrl; int frqset; } ;
struct tea5764_device {struct tea5764_regs regs; } ;

/* Variables and functions */
 int TEA5764_TNCTRL_HLSI ; 

__attribute__((used)) static void tea5764_set_freq(struct tea5764_device *radio, int freq)
{
	struct tea5764_regs *r = &radio->regs;

	/* formula: (freq [+ or -] 225000) / 8192 */
	if (r->tnctrl & TEA5764_TNCTRL_HLSI)
		r->frqset = (freq + 225000) / 8192;
	else
		r->frqset = (freq - 225000) / 8192;
}