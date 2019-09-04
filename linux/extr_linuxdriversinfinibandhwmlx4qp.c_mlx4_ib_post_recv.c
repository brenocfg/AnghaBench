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
struct ib_recv_wr {int dummy; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int _mlx4_ib_post_recv (struct ib_qp*,struct ib_recv_wr const*,struct ib_recv_wr const**,int) ; 

int mlx4_ib_post_recv(struct ib_qp *ibqp, const struct ib_recv_wr *wr,
		      const struct ib_recv_wr **bad_wr)
{
	return _mlx4_ib_post_recv(ibqp, wr, bad_wr, false);
}