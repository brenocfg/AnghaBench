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
typedef  scalar_t__ u32 ;
struct vring_desc {int dummy; } ;
struct mlxbf_tmfifo_vring {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct mlxbf_tmfifo_vdev {TYPE_1__ tx_buf; } ;

/* Variables and functions */
 scalar_t__ CIRC_SPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLXBF_TMFIFO_CON_TX_BUF_RSV_SIZE ; 
 int /*<<< orphan*/  MLXBF_TMFIFO_CON_TX_BUF_SIZE ; 
 int /*<<< orphan*/  mlxbf_tmfifo_console_output_one (struct mlxbf_tmfifo_vdev*,struct mlxbf_tmfifo_vring*,struct vring_desc*) ; 
 struct vring_desc* mlxbf_tmfifo_get_next_desc (struct mlxbf_tmfifo_vring*) ; 
 scalar_t__ mlxbf_tmfifo_get_pkt_len (struct mlxbf_tmfifo_vring*,struct vring_desc*) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_release_desc (struct mlxbf_tmfifo_vring*,struct vring_desc*,scalar_t__) ; 

__attribute__((used)) static void mlxbf_tmfifo_console_output(struct mlxbf_tmfifo_vdev *cons,
					struct mlxbf_tmfifo_vring *vring)
{
	struct vring_desc *desc;
	u32 len, avail;

	desc = mlxbf_tmfifo_get_next_desc(vring);
	while (desc) {
		/* Release the packet if not enough space. */
		len = mlxbf_tmfifo_get_pkt_len(vring, desc);
		avail = CIRC_SPACE(cons->tx_buf.head, cons->tx_buf.tail,
				   MLXBF_TMFIFO_CON_TX_BUF_SIZE);
		if (len + MLXBF_TMFIFO_CON_TX_BUF_RSV_SIZE > avail) {
			mlxbf_tmfifo_release_desc(vring, desc, len);
			break;
		}

		mlxbf_tmfifo_console_output_one(cons, vring, desc);
		mlxbf_tmfifo_release_desc(vring, desc, len);
		desc = mlxbf_tmfifo_get_next_desc(vring);
	}
}