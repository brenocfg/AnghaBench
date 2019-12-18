#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_wqe_datagram_seg {int /*<<< orphan*/  mac; int /*<<< orphan*/  vlan; void* qkey; void* dqpn; int /*<<< orphan*/  av; } ;
struct mlx4_av {int dummy; } ;
struct ib_ud_wr {int /*<<< orphan*/  ah; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; } ;
struct TYPE_4__ {TYPE_3__* mac; int /*<<< orphan*/  vlan; } ;
struct TYPE_6__ {TYPE_1__ eth; } ;
struct TYPE_5__ {TYPE_3__ av; } ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 TYPE_2__* to_mah (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_datagram_seg(struct mlx4_wqe_datagram_seg *dseg,
			     const struct ib_ud_wr *wr)
{
	memcpy(dseg->av, &to_mah(wr->ah)->av, sizeof (struct mlx4_av));
	dseg->dqpn = cpu_to_be32(wr->remote_qpn);
	dseg->qkey = cpu_to_be32(wr->remote_qkey);
	dseg->vlan = to_mah(wr->ah)->av.eth.vlan;
	memcpy(dseg->mac, to_mah(wr->ah)->av.eth.mac, 6);
}