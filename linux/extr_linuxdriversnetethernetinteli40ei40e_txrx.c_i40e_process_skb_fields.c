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
struct TYPE_4__ {int /*<<< orphan*/  status_error_len; } ;
struct TYPE_5__ {TYPE_1__ qword1; } ;
union i40e_rx_desc {TYPE_2__ wb; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct i40e_ring {int /*<<< orphan*/  netdev; int /*<<< orphan*/  queue_index; TYPE_3__* vsi; } ;
struct TYPE_6__ {int /*<<< orphan*/  back; } ;

/* Variables and functions */
 int I40E_RXD_QW1_STATUS_MASK ; 
 int I40E_RXD_QW1_STATUS_SHIFT ; 
 int I40E_RXD_QW1_STATUS_TSYNINDX_MASK ; 
 int I40E_RXD_QW1_STATUS_TSYNINDX_SHIFT ; 
 int I40E_RXD_QW1_STATUS_TSYNVALID_MASK ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_ptp_rx_hwtstamp (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  i40e_rx_checksum (TYPE_3__*,struct sk_buff*,union i40e_rx_desc*) ; 
 int /*<<< orphan*/  i40e_rx_hash (struct i40e_ring*,union i40e_rx_desc*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline
void i40e_process_skb_fields(struct i40e_ring *rx_ring,
			     union i40e_rx_desc *rx_desc, struct sk_buff *skb,
			     u8 rx_ptype)
{
	u64 qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);
	u32 rx_status = (qword & I40E_RXD_QW1_STATUS_MASK) >>
			I40E_RXD_QW1_STATUS_SHIFT;
	u32 tsynvalid = rx_status & I40E_RXD_QW1_STATUS_TSYNVALID_MASK;
	u32 tsyn = (rx_status & I40E_RXD_QW1_STATUS_TSYNINDX_MASK) >>
		   I40E_RXD_QW1_STATUS_TSYNINDX_SHIFT;

	if (unlikely(tsynvalid))
		i40e_ptp_rx_hwtstamp(rx_ring->vsi->back, skb, tsyn);

	i40e_rx_hash(rx_ring, rx_desc, skb, rx_ptype);

	i40e_rx_checksum(rx_ring->vsi, skb, rx_desc);

	skb_record_rx_queue(skb, rx_ring->queue_index);

	/* modifies the skb - consumes the enet header */
	skb->protocol = eth_type_trans(skb, rx_ring->netdev);
}