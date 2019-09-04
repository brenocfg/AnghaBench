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
struct qedr_dev {int dummy; } ;
typedef  enum qede_rdma_event { ____Placeholder_qede_rdma_event } qede_rdma_event ;

/* Variables and functions */
#define  QEDE_CHANGE_ADDR 131 
#define  QEDE_CLOSE 130 
#define  QEDE_DOWN 129 
#define  QEDE_UP 128 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  qedr_close (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_mac_address_change (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_open (struct qedr_dev*) ; 
 int /*<<< orphan*/  qedr_shutdown (struct qedr_dev*) ; 

__attribute__((used)) static void qedr_notify(struct qedr_dev *dev, enum qede_rdma_event event)
{
	switch (event) {
	case QEDE_UP:
		qedr_open(dev);
		break;
	case QEDE_DOWN:
		qedr_close(dev);
		break;
	case QEDE_CLOSE:
		qedr_shutdown(dev);
		break;
	case QEDE_CHANGE_ADDR:
		qedr_mac_address_change(dev);
		break;
	default:
		pr_err("Event not supported\n");
	}
}