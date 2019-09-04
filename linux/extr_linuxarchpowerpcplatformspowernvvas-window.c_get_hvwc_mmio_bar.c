#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct vas_window {int winid; TYPE_1__* vinst; } ;
struct TYPE_2__ {scalar_t__ hvwc_bar_start; } ;

/* Variables and functions */
 int VAS_HVWC_SIZE ; 

__attribute__((used)) static inline void get_hvwc_mmio_bar(struct vas_window *window,
			u64 *start, int *len)
{
	u64 pbaddr;

	pbaddr = window->vinst->hvwc_bar_start;
	*start = pbaddr + window->winid * VAS_HVWC_SIZE;
	*len = VAS_HVWC_SIZE;
}