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
struct iowait_work {TYPE_1__* iow; } ;
struct TYPE_2__ {struct iowait_work* wait; } ;

/* Variables and functions */
 size_t IOWAIT_IB_SE ; 
 int /*<<< orphan*/  IOWAIT_PENDING_IB ; 
 int /*<<< orphan*/  IOWAIT_PENDING_TID ; 
 int IOWAIT_TID_SE ; 
 int /*<<< orphan*/  iowait_set_flag (TYPE_1__*,int /*<<< orphan*/ ) ; 

int iowait_set_work_flag(struct iowait_work *w)
{
	if (w == &w->iow->wait[IOWAIT_IB_SE]) {
		iowait_set_flag(w->iow, IOWAIT_PENDING_IB);
		return IOWAIT_IB_SE;
	}
	iowait_set_flag(w->iow, IOWAIT_PENDING_TID);
	return IOWAIT_TID_SE;
}