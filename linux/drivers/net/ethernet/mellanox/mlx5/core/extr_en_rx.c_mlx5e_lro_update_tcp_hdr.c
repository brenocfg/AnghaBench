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
typedef  scalar_t__ u8 ;
struct tcphdr {int ack; int /*<<< orphan*/  window; int /*<<< orphan*/  ack_seq; int /*<<< orphan*/  psh; scalar_t__ check; } ;
struct mlx5_cqe64 {int /*<<< orphan*/  lro_tcp_win; int /*<<< orphan*/  lro_ack_seq_num; } ;

/* Variables and functions */
 scalar_t__ CQE_L4_HDR_TYPE_TCP_ACK_AND_DATA ; 
 scalar_t__ CQE_L4_HDR_TYPE_TCP_ACK_NO_DATA ; 
 scalar_t__ get_cqe_l4_hdr_type (struct mlx5_cqe64*) ; 
 int /*<<< orphan*/  get_cqe_lro_tcppsh (struct mlx5_cqe64*) ; 

__attribute__((used)) static void mlx5e_lro_update_tcp_hdr(struct mlx5_cqe64 *cqe, struct tcphdr *tcp)
{
	u8 l4_hdr_type = get_cqe_l4_hdr_type(cqe);
	u8 tcp_ack     = (l4_hdr_type == CQE_L4_HDR_TYPE_TCP_ACK_NO_DATA) ||
			 (l4_hdr_type == CQE_L4_HDR_TYPE_TCP_ACK_AND_DATA);

	tcp->check                      = 0;
	tcp->psh                        = get_cqe_lro_tcppsh(cqe);

	if (tcp_ack) {
		tcp->ack                = 1;
		tcp->ack_seq            = cqe->lro_ack_seq_num;
		tcp->window             = cqe->lro_tcp_win;
	}
}