#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {int total_vfs; } ;
struct TYPE_3__ {int dglort_map; } ;
struct fm10k_hw {TYPE_2__ iov; TYPE_1__ mac; } ;
struct fm10k_intfc {int glort; int glort_count; struct fm10k_hw hw; } ;

/* Variables and functions */
 int FM10K_DGLORTMAP_MASK_SHIFT ; 
 int FM10K_DGLORTMAP_NONE ; 

__attribute__((used)) static void fm10k_request_glort_range(struct fm10k_intfc *interface)
{
	struct fm10k_hw *hw = &interface->hw;
	u16 mask = (~hw->mac.dglort_map) >> FM10K_DGLORTMAP_MASK_SHIFT;

	/* establish GLORT base */
	interface->glort = hw->mac.dglort_map & FM10K_DGLORTMAP_NONE;
	interface->glort_count = 0;

	/* nothing we can do until mask is allocated */
	if (hw->mac.dglort_map == FM10K_DGLORTMAP_NONE)
		return;

	/* we support 3 possible GLORT configurations.
	 * 1: VFs consume all but the last 1
	 * 2: VFs and PF split glorts with possible gap between
	 * 3: VFs allocated first 64, all others belong to PF
	 */
	if (mask <= hw->iov.total_vfs) {
		interface->glort_count = 1;
		interface->glort += mask;
	} else if (mask < 64) {
		interface->glort_count = (mask + 1) / 2;
		interface->glort += interface->glort_count;
	} else {
		interface->glort_count = mask - 63;
		interface->glort += 64;
	}
}