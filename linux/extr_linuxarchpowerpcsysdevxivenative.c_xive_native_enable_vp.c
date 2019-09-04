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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ OPAL_BUSY ; 
 int /*<<< orphan*/  OPAL_BUSY_DELAY_MS ; 
 int /*<<< orphan*/  OPAL_XIVE_VP_ENABLED ; 
 int /*<<< orphan*/  OPAL_XIVE_VP_SINGLE_ESCALATION ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_set_vp_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int xive_native_enable_vp(u32 vp_id, bool single_escalation)
{
	s64 rc;
	u64 flags = OPAL_XIVE_VP_ENABLED;

	if (single_escalation)
		flags |= OPAL_XIVE_VP_SINGLE_ESCALATION;
	for (;;) {
		rc = opal_xive_set_vp_info(vp_id, flags, 0);
		if (rc != OPAL_BUSY)
			break;
		msleep(OPAL_BUSY_DELAY_MS);
	}
	return rc ? -EIO : 0;
}