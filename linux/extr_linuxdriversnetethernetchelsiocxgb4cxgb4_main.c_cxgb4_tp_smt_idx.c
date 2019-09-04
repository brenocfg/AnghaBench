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
typedef  enum chip_type { ____Placeholder_chip_type } chip_type ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int) ; 
 scalar_t__ CHELSIO_T5 ; 

unsigned int cxgb4_tp_smt_idx(enum chip_type chip, unsigned int viid)
{
	/* In T4/T5, SMT contains 256 SMAC entries organized in
	 * 128 rows of 2 entries each.
	 * In T6, SMT contains 256 SMAC entries in 256 rows.
	 * TODO: The below code needs to be updated when we add support
	 * for 256 VFs.
	 */
	if (CHELSIO_CHIP_VERSION(chip) <= CHELSIO_T5)
		return ((viid & 0x7f) << 1);
	else
		return (viid & 0x7f);
}