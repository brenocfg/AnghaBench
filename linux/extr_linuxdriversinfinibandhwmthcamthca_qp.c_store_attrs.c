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
struct mthca_sqp {int /*<<< orphan*/  send_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  pkey_index; } ;
struct ib_qp_attr {int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  pkey_index; } ;

/* Variables and functions */
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_QKEY ; 
 int IB_QP_SQ_PSN ; 

__attribute__((used)) static void store_attrs(struct mthca_sqp *sqp, const struct ib_qp_attr *attr,
			int attr_mask)
{
	if (attr_mask & IB_QP_PKEY_INDEX)
		sqp->pkey_index = attr->pkey_index;
	if (attr_mask & IB_QP_QKEY)
		sqp->qkey = attr->qkey;
	if (attr_mask & IB_QP_SQ_PSN)
		sqp->send_psn = attr->sq_psn;
}