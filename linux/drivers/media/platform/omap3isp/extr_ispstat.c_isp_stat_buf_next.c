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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct ispstat {int /*<<< orphan*/  active_buf; TYPE_2__ subdev; TYPE_1__* isp; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_stat_buf_find_oldest_or_empty (struct ispstat*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp_stat_buf_next(struct ispstat *stat)
{
	if (unlikely(stat->active_buf))
		/* Overwriting unused active buffer */
		dev_dbg(stat->isp->dev,
			"%s: new buffer requested without queuing active one.\n",
			stat->subdev.name);
	else
		stat->active_buf = isp_stat_buf_find_oldest_or_empty(stat);
}