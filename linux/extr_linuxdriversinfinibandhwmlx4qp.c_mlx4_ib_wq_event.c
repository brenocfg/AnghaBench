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
struct mlx4_qp {int /*<<< orphan*/  qpn; } ;
typedef  enum mlx4_event { ____Placeholder_mlx4_event } mlx4_event ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_ib_wq_event(struct mlx4_qp *qp, enum mlx4_event type)
{
	pr_warn_ratelimited("Unexpected event type %d on WQ 0x%06x. Events are not supported for WQs\n",
			    type, qp->qpn);
}