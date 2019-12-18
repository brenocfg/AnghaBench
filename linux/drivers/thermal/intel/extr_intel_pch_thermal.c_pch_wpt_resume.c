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
typedef  int u8 ;
struct pch_thermal_device {scalar_t__ hw_base; scalar_t__ bios_enabled; } ;

/* Variables and functions */
 scalar_t__ WPT_TSEL ; 
 int WPT_TSEL_ETS ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int pch_wpt_resume(struct pch_thermal_device *ptd)
{
	u8 tsel;

	if (ptd->bios_enabled)
		return 0;

	tsel = readb(ptd->hw_base + WPT_TSEL);

	writeb(tsel | WPT_TSEL_ETS, ptd->hw_base + WPT_TSEL);

	return 0;
}