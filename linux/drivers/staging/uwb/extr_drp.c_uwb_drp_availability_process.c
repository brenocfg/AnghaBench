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
struct uwb_rc {int dummy; } ;
struct uwb_ie_drp_avail {int /*<<< orphan*/  bmp; } ;
struct uwb_dev {int /*<<< orphan*/  last_availability_bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_NUM_MAS ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uwb_drp_availability_process(struct uwb_rc *rc, struct uwb_dev *src,
					 struct uwb_ie_drp_avail *drp_availability_ie)
{
	bitmap_copy(src->last_availability_bm,
		    drp_availability_ie->bmp, UWB_NUM_MAS);
}