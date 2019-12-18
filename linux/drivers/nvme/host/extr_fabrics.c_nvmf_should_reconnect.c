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
struct nvme_ctrl {int nr_reconnects; TYPE_1__* opts; } ;
struct TYPE_2__ {int max_reconnects; } ;

/* Variables and functions */

bool nvmf_should_reconnect(struct nvme_ctrl *ctrl)
{
	if (ctrl->opts->max_reconnects == -1 ||
	    ctrl->nr_reconnects < ctrl->opts->max_reconnects)
		return true;

	return false;
}