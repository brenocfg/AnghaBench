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
struct ispstat {scalar_t__ state; int /*<<< orphan*/  buf_err; } ;

/* Variables and functions */
 scalar_t__ ISPSTAT_ENABLED ; 
 int STAT_BUF_DONE ; 
 int STAT_NO_BUF ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_stat_buf_next (struct ispstat*) ; 
 int isp_stat_buf_queue (struct ispstat*) ; 

__attribute__((used)) static int isp_stat_buf_process(struct ispstat *stat, int buf_state)
{
	int ret = STAT_NO_BUF;

	if (!atomic_add_unless(&stat->buf_err, -1, 0) &&
	    buf_state == STAT_BUF_DONE && stat->state == ISPSTAT_ENABLED) {
		ret = isp_stat_buf_queue(stat);
		isp_stat_buf_next(stat);
	}

	return ret;
}