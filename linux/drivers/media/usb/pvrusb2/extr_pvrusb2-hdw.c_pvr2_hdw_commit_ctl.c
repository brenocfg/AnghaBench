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
struct pvr2_hdw {int /*<<< orphan*/  big_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_GIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TAKE (int /*<<< orphan*/ ) ; 
 int pvr2_hdw_commit_setup (struct pvr2_hdw*) ; 
 int pvr2_hdw_wait (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

int pvr2_hdw_commit_ctl(struct pvr2_hdw *hdw)
{
	int fl;
	LOCK_TAKE(hdw->big_lock);
	fl = pvr2_hdw_commit_setup(hdw);
	LOCK_GIVE(hdw->big_lock);
	if (!fl) return 0;
	return pvr2_hdw_wait(hdw,0);
}