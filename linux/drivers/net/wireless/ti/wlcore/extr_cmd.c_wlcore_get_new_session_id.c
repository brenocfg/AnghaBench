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
typedef  size_t u8 ;
struct wl1271 {scalar_t__* session_ids; } ;

/* Variables and functions */
 scalar_t__ SESSION_COUNTER_MAX ; 

__attribute__((used)) static int wlcore_get_new_session_id(struct wl1271 *wl, u8 hlid)
{
	if (wl->session_ids[hlid] >= SESSION_COUNTER_MAX)
		wl->session_ids[hlid] = 0;

	wl->session_ids[hlid]++;

	return wl->session_ids[hlid];
}