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
struct mlx5_core_cq {int /*<<< orphan*/  cqn; } ;
typedef  enum mlx5_event { ____Placeholder_mlx5_event } mlx5_event ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dr_cq_event(struct mlx5_core_cq *mcq,
			enum mlx5_event event)
{
	pr_info("CQ event %u on CQ #%u\n", event, mcq->cqn);
}