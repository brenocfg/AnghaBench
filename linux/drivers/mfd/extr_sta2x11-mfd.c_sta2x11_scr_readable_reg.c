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
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int STA2X11_SECR_CR ; 
 int /*<<< orphan*/  STA2X11_SECR_FVR0 ; 
 int /*<<< orphan*/  STA2X11_SECR_FVR1 ; 
 scalar_t__ __reg_within_range (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sta2x11_scr_readable_reg(struct device *dev, unsigned int reg)
{
	return (reg == STA2X11_SECR_CR) ||
		__reg_within_range(reg, STA2X11_SECR_FVR0, STA2X11_SECR_FVR1);
}