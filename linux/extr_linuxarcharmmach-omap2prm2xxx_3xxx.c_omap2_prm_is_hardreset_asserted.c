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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_RM_RSTCTRL ; 
 int omap2_prm_read_mod_bits_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int omap2_prm_is_hardreset_asserted(u8 shift, u8 part, s16 prm_mod, u16 offset)
{
	return omap2_prm_read_mod_bits_shift(prm_mod, OMAP2_RM_RSTCTRL,
				       (1 << shift));
}