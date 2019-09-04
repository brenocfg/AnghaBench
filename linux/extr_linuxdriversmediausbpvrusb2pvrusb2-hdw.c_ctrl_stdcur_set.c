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
typedef  int v4l2_std_id ;
struct pvr2_hdw {int std_mask_cur; int std_dirty; } ;
struct pvr2_ctrl {struct pvr2_hdw* hdw; } ;

/* Variables and functions */

__attribute__((used)) static int ctrl_stdcur_set(struct pvr2_ctrl *cptr,int m,int v)
{
	struct pvr2_hdw *hdw = cptr->hdw;
	v4l2_std_id ns;
	ns = hdw->std_mask_cur;
	ns = (ns & ~m) | (v & m);
	if (ns == hdw->std_mask_cur) return 0;
	hdw->std_mask_cur = ns;
	hdw->std_dirty = !0;
	return 0;
}