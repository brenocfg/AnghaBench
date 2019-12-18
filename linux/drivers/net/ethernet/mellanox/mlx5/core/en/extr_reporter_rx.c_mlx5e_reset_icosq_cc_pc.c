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
struct mlx5e_icosq {scalar_t__ cc; scalar_t__ pc; int /*<<< orphan*/  sqn; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mlx5e_reset_icosq_cc_pc(struct mlx5e_icosq *icosq)
{
	WARN_ONCE(icosq->cc != icosq->pc, "ICOSQ 0x%x: cc (0x%x) != pc (0x%x)\n",
		  icosq->sqn, icosq->cc, icosq->pc);
	icosq->cc = 0;
	icosq->pc = 0;
}