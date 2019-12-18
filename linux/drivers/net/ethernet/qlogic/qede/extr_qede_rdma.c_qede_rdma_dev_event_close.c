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
struct qede_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDE_DOWN ; 
 int /*<<< orphan*/  qede_rdma_add_event (struct qede_dev*,int /*<<< orphan*/ ) ; 

void qede_rdma_dev_event_close(struct qede_dev *edev)
{
	qede_rdma_add_event(edev, QEDE_DOWN);
}