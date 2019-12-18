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
struct mlx5dr_cq {int dummy; } ;

/* Variables and functions */
 int CQ_OK ; 
 int CQ_POLL_ERR ; 
 int dr_cq_poll_one (struct mlx5dr_cq*) ; 

__attribute__((used)) static int dr_poll_cq(struct mlx5dr_cq *dr_cq, int ne)
{
	int npolled;
	int err = 0;

	for (npolled = 0; npolled < ne; ++npolled) {
		err = dr_cq_poll_one(dr_cq);
		if (err != CQ_OK)
			break;
	}

	return err == CQ_POLL_ERR ? err : npolled;
}