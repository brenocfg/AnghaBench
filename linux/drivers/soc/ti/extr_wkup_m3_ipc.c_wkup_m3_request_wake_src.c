#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wkup_m3_ipc {int dummy; } ;
struct TYPE_3__ {unsigned int irq_nr; char const* src; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int M3_WAKE_SRC_MASK ; 
 TYPE_1__* wakeups ; 
 int wkup_m3_ctrl_ipc_read (struct wkup_m3_ipc*,int) ; 

__attribute__((used)) static const char *wkup_m3_request_wake_src(struct wkup_m3_ipc *m3_ipc)
{
	unsigned int wakeup_src_idx;
	int j, val;

	val = wkup_m3_ctrl_ipc_read(m3_ipc, 6);

	wakeup_src_idx = val & M3_WAKE_SRC_MASK;

	for (j = 0; j < ARRAY_SIZE(wakeups) - 1; j++) {
		if (wakeups[j].irq_nr == wakeup_src_idx)
			return wakeups[j].src;
	}
	return wakeups[j].src;
}