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

/* Variables and functions */
 int /*<<< orphan*/  PVR_970 ; 
 int /*<<< orphan*/  PVR_970FX ; 
 int /*<<< orphan*/  PVR_970GX ; 
 int /*<<< orphan*/  PVR_970MP ; 
 int /*<<< orphan*/  PVR_POWER4 ; 
 int /*<<< orphan*/  PVR_POWER4p ; 
 scalar_t__ pvr_version_is (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mmcra_must_set_sample(void)
{
	if (pvr_version_is(PVR_POWER4) || pvr_version_is(PVR_POWER4p) ||
	    pvr_version_is(PVR_970) || pvr_version_is(PVR_970FX) ||
	    pvr_version_is(PVR_970MP) || pvr_version_is(PVR_970GX))
		return 1;

	return 0;
}