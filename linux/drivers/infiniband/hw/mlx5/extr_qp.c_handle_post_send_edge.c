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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_wq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _handle_post_send_edge (struct mlx5_ib_wq*,void**,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline void handle_post_send_edge(struct mlx5_ib_wq *sq, void **seg,
					 u32 wqe_sz, void **cur_edge)
{
	if (likely(*seg != *cur_edge))
		return;

	_handle_post_send_edge(sq, seg, wqe_sz, cur_edge);
}