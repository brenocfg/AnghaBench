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
struct mlx5_core_qp {int /*<<< orphan*/  qpn; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dr_qp_event(struct mlx5_core_qp *mqp, int event)
{
	pr_info("DR QP event %u on QP #%u\n", event, mqp->qpn);
}