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
union drbd_dev_state {scalar_t__ pdsk; scalar_t__ conn; } ;

/* Variables and functions */
 scalar_t__ C_AHEAD ; 
 scalar_t__ C_WF_BITMAP_T ; 
 scalar_t__ D_INCONSISTENT ; 
 scalar_t__ D_UP_TO_DATE ; 

bool drbd_should_do_remote(union drbd_dev_state s)
{
	return s.pdsk == D_UP_TO_DATE ||
		(s.pdsk >= D_INCONSISTENT &&
		 s.conn >= C_WF_BITMAP_T &&
		 s.conn < C_AHEAD);
	/* Before proto 96 that was >= CONNECTED instead of >= C_WF_BITMAP_T.
	   That is equivalent since before 96 IO was frozen in the C_WF_BITMAP*
	   states. */
}