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
struct ib_qp {scalar_t__ qp_type; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 scalar_t__ IB_QPT_XRC_INI ; 
 scalar_t__ IB_QPT_XRC_TGT ; 

__attribute__((used)) static bool is_qp_type_connected(const struct ib_qp *qp)
{
	return (qp->qp_type == IB_QPT_UC ||
		qp->qp_type == IB_QPT_RC ||
		qp->qp_type == IB_QPT_XRC_INI ||
		qp->qp_type == IB_QPT_XRC_TGT);
}