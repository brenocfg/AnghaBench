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
typedef  int u32 ;
struct hw_atl_txd_s {int ctl; int ctl2; scalar_t__ buf_addr; } ;
struct aq_ring_s {size_t sw_tail; struct aq_ring_buff_s* buff_ring; int /*<<< orphan*/ * dx_ring; } ;
struct aq_ring_buff_s {unsigned int len; unsigned int len_pkt; int len_l3; int len_l2; int mss; int len_l4; scalar_t__ is_eop; scalar_t__ is_tcp_cso; scalar_t__ is_udp_cso; scalar_t__ is_ip_cso; scalar_t__ pa; scalar_t__ is_ipv6; scalar_t__ is_gso; scalar_t__ is_sop; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 unsigned int HW_ATL_A0_TXD_CTL2_CTX_EN ; 
 unsigned int HW_ATL_A0_TXD_CTL2_LEN ; 
 int HW_ATL_A0_TXD_CTL_BLEN ; 
 int HW_ATL_A0_TXD_CTL_CMD_IPCSO ; 
 int HW_ATL_A0_TXD_CTL_CMD_IPV6 ; 
 int HW_ATL_A0_TXD_CTL_CMD_LSO ; 
 int HW_ATL_A0_TXD_CTL_CMD_TCP ; 
 int HW_ATL_A0_TXD_CTL_CMD_TUCSO ; 
 int HW_ATL_A0_TXD_CTL_CMD_WB ; 
 int HW_ATL_A0_TXD_CTL_DESC_TYPE_TXC ; 
 int HW_ATL_A0_TXD_CTL_DESC_TYPE_TXD ; 
 int HW_ATL_A0_TXD_CTL_EOP ; 
 size_t HW_ATL_A0_TXD_SIZE ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 size_t aq_ring_next_dx (struct aq_ring_s*,size_t) ; 
 int /*<<< orphan*/  hw_atl_a0_hw_tx_ring_tail_update (struct aq_hw_s*,struct aq_ring_s*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static int hw_atl_a0_hw_ring_tx_xmit(struct aq_hw_s *self,
				     struct aq_ring_s *ring,
				     unsigned int frags)
{
	struct aq_ring_buff_s *buff = NULL;
	struct hw_atl_txd_s *txd = NULL;
	unsigned int buff_pa_len = 0U;
	unsigned int pkt_len = 0U;
	unsigned int frag_count = 0U;
	bool is_gso = false;

	buff = &ring->buff_ring[ring->sw_tail];
	pkt_len = (buff->is_eop && buff->is_sop) ? buff->len : buff->len_pkt;

	for (frag_count = 0; frag_count < frags; frag_count++) {
		txd = (struct hw_atl_txd_s *)&ring->dx_ring[ring->sw_tail *
						HW_ATL_A0_TXD_SIZE];
		txd->ctl = 0;
		txd->ctl2 = 0;
		txd->buf_addr = 0;

		buff = &ring->buff_ring[ring->sw_tail];

		if (buff->is_gso) {
			txd->ctl |= (buff->len_l3 << 31) |
				(buff->len_l2 << 24) |
				HW_ATL_A0_TXD_CTL_CMD_TCP |
				HW_ATL_A0_TXD_CTL_DESC_TYPE_TXC;
			txd->ctl2 |= (buff->mss << 16) |
				(buff->len_l4 << 8) |
				(buff->len_l3 >> 1);

			pkt_len -= (buff->len_l4 +
				    buff->len_l3 +
				    buff->len_l2);
			is_gso = true;

			if (buff->is_ipv6)
				txd->ctl |= HW_ATL_A0_TXD_CTL_CMD_IPV6;
		} else {
			buff_pa_len = buff->len;

			txd->buf_addr = buff->pa;
			txd->ctl |= (HW_ATL_A0_TXD_CTL_BLEN &
						((u32)buff_pa_len << 4));
			txd->ctl |= HW_ATL_A0_TXD_CTL_DESC_TYPE_TXD;
			/* PAY_LEN */
			txd->ctl2 |= HW_ATL_A0_TXD_CTL2_LEN & (pkt_len << 14);

			if (is_gso) {
				txd->ctl |= HW_ATL_A0_TXD_CTL_CMD_LSO;
				txd->ctl2 |= HW_ATL_A0_TXD_CTL2_CTX_EN;
			}

			/* Tx checksum offloads */
			if (buff->is_ip_cso)
				txd->ctl |= HW_ATL_A0_TXD_CTL_CMD_IPCSO;

			if (buff->is_udp_cso || buff->is_tcp_cso)
				txd->ctl |= HW_ATL_A0_TXD_CTL_CMD_TUCSO;

			if (unlikely(buff->is_eop)) {
				txd->ctl |= HW_ATL_A0_TXD_CTL_EOP;
				txd->ctl |= HW_ATL_A0_TXD_CTL_CMD_WB;
				is_gso = false;
			}
		}

		ring->sw_tail = aq_ring_next_dx(ring, ring->sw_tail);
	}

	hw_atl_a0_hw_tx_ring_tail_update(self, ring);
	return aq_hw_err_from_flags(self);
}