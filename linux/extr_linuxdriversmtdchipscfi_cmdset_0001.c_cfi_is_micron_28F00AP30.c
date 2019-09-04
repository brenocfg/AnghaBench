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
struct flchip {int dummy; } ;
struct cfi_private {scalar_t__ mfr; scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ CFI_MFR_INTEL ; 
 scalar_t__ M28F00AP30 ; 

__attribute__((used)) static int cfi_is_micron_28F00AP30(struct cfi_private *cfi, struct flchip *chip)
{
	/*
	 * Micron(was Numonyx) 1Gbit bottom boot are buggy w.r.t
	 * Erase Supend for their small Erase Blocks(0x8000)
	 */
	if (cfi->mfr == CFI_MFR_INTEL && cfi->id == M28F00AP30)
		return 1;
	return 0;
}