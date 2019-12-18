#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rss; } ;
struct TYPE_10__ {TYPE_3__ hi_dword; } ;
struct TYPE_7__ {int const status_error_len; } ;
struct TYPE_9__ {TYPE_5__ qword0; TYPE_2__ qword1; } ;
union iavf_rx_desc {TYPE_4__ wb; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct iavf_ring {TYPE_1__* netdev; } ;
typedef  int __le64 ;
struct TYPE_6__ {int features; } ;

/* Variables and functions */
 scalar_t__ IAVF_RX_DESC_FLTSTAT_RSS_HASH ; 
 int IAVF_RX_DESC_STATUS_FLTSTAT_SHIFT ; 
 int NETIF_F_RXHASH ; 
 int cpu_to_le64 (int) ; 
 int /*<<< orphan*/  iavf_ptype_to_htype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iavf_rx_hash(struct iavf_ring *ring,
				union iavf_rx_desc *rx_desc,
				struct sk_buff *skb,
				u8 rx_ptype)
{
	u32 hash;
	const __le64 rss_mask =
		cpu_to_le64((u64)IAVF_RX_DESC_FLTSTAT_RSS_HASH <<
			    IAVF_RX_DESC_STATUS_FLTSTAT_SHIFT);

	if (ring->netdev->features & NETIF_F_RXHASH)
		return;

	if ((rx_desc->wb.qword1.status_error_len & rss_mask) == rss_mask) {
		hash = le32_to_cpu(rx_desc->wb.qword0.hi_dword.rss);
		skb_set_hash(skb, hash, iavf_ptype_to_htype(rx_ptype));
	}
}