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
struct cfi_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfi_udelay (int) ; 
 scalar_t__ is_m29ew (struct cfi_private*) ; 

__attribute__((used)) static void cfi_fixup_m29ew_delay_after_resume(struct cfi_private *cfi)
{
	/*
	 * Resolving the Delay After Resume Issue see Micron TN-13-07
	 * Worst case delay must be 500µs but 30-50µs should be ok as well
	 */
	if (is_m29ew(cfi))
		cfi_udelay(500);
}