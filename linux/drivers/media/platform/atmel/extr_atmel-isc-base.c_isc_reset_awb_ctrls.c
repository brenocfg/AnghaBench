#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* gain; int /*<<< orphan*/ * offset; } ;
struct isc_device {TYPE_1__ ctrls; } ;

/* Variables and functions */
 unsigned int ISC_HIS_CFG_MODE_B ; 
 unsigned int ISC_HIS_CFG_MODE_GR ; 
 int /*<<< orphan*/  ISC_WB_O_ZERO_VAL ; 

__attribute__((used)) static inline void isc_reset_awb_ctrls(struct isc_device *isc)
{
	unsigned int c;

	for (c = ISC_HIS_CFG_MODE_GR; c <= ISC_HIS_CFG_MODE_B; c++) {
		/* gains have a fixed point at 9 decimals */
		isc->ctrls.gain[c] = 1 << 9;
		/* offsets are in 2's complements, the value
		 * will be substracted from ISC_WB_O_ZERO_VAL to obtain
		 * 2's complement of a value between 0 and
		 * ISC_WB_O_ZERO_VAL >> 1
		 */
		isc->ctrls.offset[c] = ISC_WB_O_ZERO_VAL;
	}
}