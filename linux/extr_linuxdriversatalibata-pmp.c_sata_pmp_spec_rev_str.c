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
typedef  int u32 ;

/* Variables and functions */
 size_t SATA_PMP_GSCR_REV ; 

__attribute__((used)) static const char *sata_pmp_spec_rev_str(const u32 *gscr)
{
	u32 rev = gscr[SATA_PMP_GSCR_REV];

	if (rev & (1 << 3))
		return "1.2";
	if (rev & (1 << 2))
		return "1.1";
	if (rev & (1 << 1))
		return "1.0";
	return "<unknown>";
}