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
struct cfi_private {scalar_t__ mfr; scalar_t__ device_type; int id; } ;

/* Variables and functions */
 scalar_t__ CFI_DEVICETYPE_X16 ; 
 scalar_t__ CFI_DEVICETYPE_X8 ; 
 scalar_t__ CFI_MFR_INTEL ; 

__attribute__((used)) static int is_m29ew(struct cfi_private *cfi)
{
	if (cfi->mfr == CFI_MFR_INTEL &&
	    ((cfi->device_type == CFI_DEVICETYPE_X8 && (cfi->id & 0xff) == 0x7e) ||
	     (cfi->device_type == CFI_DEVICETYPE_X16 && cfi->id == 0x227e)))
		return 1;
	return 0;
}