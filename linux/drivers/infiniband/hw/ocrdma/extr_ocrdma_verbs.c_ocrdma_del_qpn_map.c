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
struct ocrdma_qp {size_t id; } ;
struct ocrdma_dev {int /*<<< orphan*/ ** qp_tbl; } ;

/* Variables and functions */

__attribute__((used)) static void ocrdma_del_qpn_map(struct ocrdma_dev *dev, struct ocrdma_qp *qp)
{
	dev->qp_tbl[qp->id] = NULL;
}