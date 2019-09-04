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
struct TYPE_2__ {int cmd; scalar_t__ opt; } ;
struct wiimote_data {TYPE_1__ state; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */

__attribute__((used)) static inline bool wiimote_cmd_pending(struct wiimote_data *wdata, int cmd,
								__u32 opt)
{
	return wdata->state.cmd == cmd && wdata->state.opt == opt;
}