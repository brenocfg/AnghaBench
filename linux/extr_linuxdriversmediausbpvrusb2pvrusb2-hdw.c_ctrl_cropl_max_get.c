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
struct TYPE_3__ {int left; scalar_t__ width; } ;
struct v4l2_cropcap {TYPE_1__ bounds; } ;
struct pvr2_ctrl {TYPE_2__* hdw; } ;
struct TYPE_4__ {scalar_t__ cropw_val; struct v4l2_cropcap cropcap_info; } ;

/* Variables and functions */
 int pvr2_hdw_check_cropcap (TYPE_2__*) ; 

__attribute__((used)) static int ctrl_cropl_max_get(struct pvr2_ctrl *cptr, int *left)
{
	struct v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	int stat = pvr2_hdw_check_cropcap(cptr->hdw);
	if (stat != 0) {
		return stat;
	}
	*left = cap->bounds.left;
	if (cap->bounds.width > cptr->hdw->cropw_val) {
		*left += cap->bounds.width - cptr->hdw->cropw_val;
	}
	return 0;
}