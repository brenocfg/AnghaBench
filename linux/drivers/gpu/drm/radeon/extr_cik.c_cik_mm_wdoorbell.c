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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ num_doorbells; scalar_t__ ptr; } ;
struct radeon_device {TYPE_1__ doorbell; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

void cik_mm_wdoorbell(struct radeon_device *rdev, u32 index, u32 v)
{
	if (index < rdev->doorbell.num_doorbells) {
		writel(v, rdev->doorbell.ptr + index);
	} else {
		DRM_ERROR("writing beyond doorbell aperture: 0x%08x!\n", index);
	}
}