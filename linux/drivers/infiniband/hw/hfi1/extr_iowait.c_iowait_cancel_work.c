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
struct iowait {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  iowork; } ;
struct TYPE_3__ {int /*<<< orphan*/  iowork; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_2__* iowait_get_ib_work (struct iowait*) ; 
 TYPE_1__* iowait_get_tid_work (struct iowait*) ; 

void iowait_cancel_work(struct iowait *w)
{
	cancel_work_sync(&iowait_get_ib_work(w)->iowork);
	cancel_work_sync(&iowait_get_tid_work(w)->iowork);
}