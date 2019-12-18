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
struct TYPE_2__ {int ie_valid; int /*<<< orphan*/  local; int /*<<< orphan*/  pending; } ;
struct uwb_rc {TYPE_1__ drp_avail; } ;
struct uwb_mas_bm {int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_NUM_MAS ; 
 int /*<<< orphan*/  bitmap_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uwb_drp_avail_reserve(struct uwb_rc *rc, struct uwb_mas_bm *mas)
{
	bitmap_or(rc->drp_avail.pending, rc->drp_avail.pending, mas->bm, UWB_NUM_MAS);
	bitmap_andnot(rc->drp_avail.local, rc->drp_avail.local, mas->bm, UWB_NUM_MAS);
	rc->drp_avail.ie_valid = false;
}