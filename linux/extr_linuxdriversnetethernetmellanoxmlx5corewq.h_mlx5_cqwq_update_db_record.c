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
struct mlx5_cqwq {int cc; int /*<<< orphan*/ * db; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static inline void mlx5_cqwq_update_db_record(struct mlx5_cqwq *wq)
{
	*wq->db = cpu_to_be32(wq->cc & 0xffffff);
}