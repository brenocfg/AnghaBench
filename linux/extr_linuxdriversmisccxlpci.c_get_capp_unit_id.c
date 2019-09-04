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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P8_CAPP_UNIT0_ID ; 
 int /*<<< orphan*/  P8_CAPP_UNIT1_ID ; 
 int /*<<< orphan*/  P9_CAPP_UNIT0_ID ; 
 int /*<<< orphan*/  P9_CAPP_UNIT1_ID ; 
 int /*<<< orphan*/  PVR_POWER8NVL ; 
 scalar_t__ cxl_is_power8 () ; 
 scalar_t__ cxl_is_power9 () ; 
 int /*<<< orphan*/  pvr_version_is (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 get_capp_unit_id(struct device_node *np, u32 phb_index)
{
	/*
	 * POWER 8:
	 *  - For chips other than POWER8NVL, we only have CAPP 0,
	 *    irrespective of which PHB is used.
	 *  - For POWER8NVL, assume CAPP 0 is attached to PHB0 and
	 *    CAPP 1 is attached to PHB1.
	 */
	if (cxl_is_power8()) {
		if (!pvr_version_is(PVR_POWER8NVL))
			return P8_CAPP_UNIT0_ID;

		if (phb_index == 0)
			return P8_CAPP_UNIT0_ID;

		if (phb_index == 1)
			return P8_CAPP_UNIT1_ID;
	}

	/*
	 * POWER 9:
	 *   PEC0 (PHB0). Capp ID = CAPP0 (0b1100_0000)
	 *   PEC1 (PHB1 - PHB2). No capi mode
	 *   PEC2 (PHB3 - PHB4 - PHB5): Capi mode on PHB3 only. Capp ID = CAPP1 (0b1110_0000)
	 */
	if (cxl_is_power9()) {
		if (phb_index == 0)
			return P9_CAPP_UNIT0_ID;

		if (phb_index == 3)
			return P9_CAPP_UNIT1_ID;
	}

	return 0;
}