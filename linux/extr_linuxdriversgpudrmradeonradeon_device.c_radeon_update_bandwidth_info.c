#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {void* full; } ;
struct TYPE_6__ {void* full; } ;
struct TYPE_7__ {int current_sclk; int current_mclk; TYPE_4__ sclk; TYPE_1__ core_bandwidth; TYPE_4__ mclk; } ;
struct radeon_device {int flags; TYPE_2__ pm; } ;
struct TYPE_8__ {void* full; } ;
typedef  TYPE_3__ fixed20_12 ;

/* Variables and functions */
 int RADEON_IS_IGP ; 
 void* dfixed_const (int) ; 
 void* dfixed_div (TYPE_4__,TYPE_3__) ; 

void radeon_update_bandwidth_info(struct radeon_device *rdev)
{
	fixed20_12 a;
	u32 sclk = rdev->pm.current_sclk;
	u32 mclk = rdev->pm.current_mclk;

	/* sclk/mclk in Mhz */
	a.full = dfixed_const(100);
	rdev->pm.sclk.full = dfixed_const(sclk);
	rdev->pm.sclk.full = dfixed_div(rdev->pm.sclk, a);
	rdev->pm.mclk.full = dfixed_const(mclk);
	rdev->pm.mclk.full = dfixed_div(rdev->pm.mclk, a);

	if (rdev->flags & RADEON_IS_IGP) {
		a.full = dfixed_const(16);
		/* core_bandwidth = sclk(Mhz) * 16 */
		rdev->pm.core_bandwidth.full = dfixed_div(rdev->pm.sclk, a);
	}
}