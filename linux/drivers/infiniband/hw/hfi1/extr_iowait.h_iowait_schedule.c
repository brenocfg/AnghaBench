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
struct workqueue_struct {int dummy; } ;
struct iowait {TYPE_1__* wait; } ;
struct TYPE_2__ {int /*<<< orphan*/  iowork; } ;

/* Variables and functions */
 size_t IOWAIT_IB_SE ; 
 int /*<<< orphan*/  queue_work_on (int,struct workqueue_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool iowait_schedule(struct iowait *wait,
				   struct workqueue_struct *wq, int cpu)
{
	return !!queue_work_on(cpu, wq, &wait->wait[IOWAIT_IB_SE].iowork);
}