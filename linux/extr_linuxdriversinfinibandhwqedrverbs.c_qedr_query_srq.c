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
struct qedr_srq {int /*<<< orphan*/  srq_limit; } ;
struct qedr_device_attr {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_srq_wr; } ;
struct qedr_dev {struct qedr_device_attr attr; } ;
struct ib_srq_attr {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; int /*<<< orphan*/  srq_limit; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 struct qedr_srq* get_qedr_srq (struct ib_srq*) ; 

int qedr_query_srq(struct ib_srq *ibsrq, struct ib_srq_attr *srq_attr)
{
	struct qedr_dev *dev = get_qedr_dev(ibsrq->device);
	struct qedr_device_attr *qattr = &dev->attr;
	struct qedr_srq *srq = get_qedr_srq(ibsrq);

	srq_attr->srq_limit = srq->srq_limit;
	srq_attr->max_wr = qattr->max_srq_wr;
	srq_attr->max_sge = qattr->max_sge;

	return 0;
}