#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct TYPE_6__ {int valid_bits; } ;
struct TYPE_4__ {TYPE_3__ type_bitmask; } ;
struct TYPE_5__ {TYPE_1__ def; } ;
struct pvr2_hdw {int std_mask_avail; TYPE_2__ std_info_cur; } ;
struct pvr2_ctrl {struct pvr2_hdw* hdw; } ;

/* Variables and functions */

__attribute__((used)) static int ctrl_stdavail_set(struct pvr2_ctrl *cptr,int m,int v)
{
	struct pvr2_hdw *hdw = cptr->hdw;
	v4l2_std_id ns;
	ns = hdw->std_mask_avail;
	ns = (ns & ~m) | (v & m);
	if (ns == hdw->std_mask_avail) return 0;
	hdw->std_mask_avail = ns;
	hdw->std_info_cur.def.type_bitmask.valid_bits = hdw->std_mask_avail;
	return 0;
}