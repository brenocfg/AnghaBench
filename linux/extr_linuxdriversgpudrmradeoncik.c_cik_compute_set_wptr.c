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
struct radeon_ring {int wptr_offs; int /*<<< orphan*/  wptr; int /*<<< orphan*/  doorbell_index; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; } ;
struct radeon_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDOORBELL32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cik_compute_set_wptr(struct radeon_device *rdev,
			  struct radeon_ring *ring)
{
	/* XXX check if swapping is necessary on BE */
	rdev->wb.wb[ring->wptr_offs/4] = ring->wptr;
	WDOORBELL32(ring->doorbell_index, ring->wptr);
}