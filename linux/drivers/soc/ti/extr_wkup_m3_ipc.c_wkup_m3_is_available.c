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
struct wkup_m3_ipc {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ M3_STATE_RESET ; 
 scalar_t__ M3_STATE_UNKNOWN ; 

__attribute__((used)) static int wkup_m3_is_available(struct wkup_m3_ipc *m3_ipc)
{
	return ((m3_ipc->state != M3_STATE_RESET) &&
		(m3_ipc->state != M3_STATE_UNKNOWN));
}