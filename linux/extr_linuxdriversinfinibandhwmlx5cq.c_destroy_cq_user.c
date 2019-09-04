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
struct TYPE_2__ {int /*<<< orphan*/  umem; } ;
struct mlx5_ib_cq {TYPE_1__ buf; int /*<<< orphan*/  db; } ;
struct ib_ucontext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_db_unmap_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static void destroy_cq_user(struct mlx5_ib_cq *cq, struct ib_ucontext *context)
{
	mlx5_ib_db_unmap_user(to_mucontext(context), &cq->db);
	ib_umem_release(cq->buf.umem);
}