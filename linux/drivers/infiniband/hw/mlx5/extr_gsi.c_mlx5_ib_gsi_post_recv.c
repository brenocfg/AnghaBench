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
struct mlx5_ib_gsi_qp {int /*<<< orphan*/  rx_qp; } ;
struct ib_recv_wr {int dummy; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 struct mlx5_ib_gsi_qp* gsi_qp (struct ib_qp*) ; 
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr const*,struct ib_recv_wr const**) ; 

int mlx5_ib_gsi_post_recv(struct ib_qp *qp, const struct ib_recv_wr *wr,
			  const struct ib_recv_wr **bad_wr)
{
	struct mlx5_ib_gsi_qp *gsi = gsi_qp(qp);

	return ib_post_recv(gsi->rx_qp, wr, bad_wr);
}