#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int total_pkt_len; } ;
struct TYPE_6__ {TYPE_1__ pkt_len; } ;
struct TYPE_8__ {int buf1_size; int /*<<< orphan*/  cksum_ctl; TYPE_2__ tx_pkt_len; int /*<<< orphan*/  first_desc; } ;
struct TYPE_7__ {TYPE_4__ tx_rd_des23; } ;
struct sxgbe_tx_norm_desc {TYPE_3__ tdes23; } ;

/* Variables and functions */
 int /*<<< orphan*/  cic_full ; 

__attribute__((used)) static void sxgbe_prepare_tx_desc(struct sxgbe_tx_norm_desc *p, u8 is_fd,
				  int buf1_len, int pkt_len, int cksum)
{
	p->tdes23.tx_rd_des23.first_desc = is_fd;
	p->tdes23.tx_rd_des23.buf1_size = buf1_len;

	p->tdes23.tx_rd_des23.tx_pkt_len.pkt_len.total_pkt_len = pkt_len;

	if (cksum)
		p->tdes23.tx_rd_des23.cksum_ctl = cic_full;
}