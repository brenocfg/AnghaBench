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
struct v4l2_cropcap {int dummy; } ;
struct pvr2_hdw {int /*<<< orphan*/  big_lock; int /*<<< orphan*/  cropcap_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_cropcap*,int /*<<< orphan*/ *,int) ; 
 int pvr2_hdw_check_cropcap (struct pvr2_hdw*) ; 

int pvr2_hdw_get_cropcap(struct pvr2_hdw *hdw, struct v4l2_cropcap *pp)
{
	int stat = 0;
	LOCK_TAKE(hdw->big_lock);
	stat = pvr2_hdw_check_cropcap(hdw);
	if (!stat) {
		memcpy(pp, &hdw->cropcap_info, sizeof(hdw->cropcap_info));
	}
	LOCK_GIVE(hdw->big_lock);
	return stat;
}