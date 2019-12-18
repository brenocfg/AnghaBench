#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u16 ;
struct TYPE_15__ {scalar_t__* d; } ;
struct wil_tx_enhanced_desc {TYPE_7__ mac; } ;
struct TYPE_10__ {int /*<<< orphan*/  buff_id; } ;
struct wil_rx_enhanced_desc {TYPE_2__ mac; } ;
struct wil_ring {TYPE_8__* ctx; TYPE_6__* va; scalar_t__ is_rx; } ;
struct TYPE_12__ {TYPE_3__* buff_arr; int /*<<< orphan*/  size; } ;
struct wil6210_priv {TYPE_4__ rx_buff_mgmt; } ;
struct seq_file {int dummy; } ;
struct TYPE_16__ {scalar_t__ skb; } ;
struct TYPE_13__ {int /*<<< orphan*/  enhanced; } ;
struct TYPE_9__ {int /*<<< orphan*/  enhanced; } ;
struct TYPE_14__ {TYPE_5__ tx; TYPE_1__ rx; } ;
struct TYPE_11__ {int skb; } ;

/* Variables and functions */
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char) ; 
 scalar_t__ wil_val_in_range (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wil_print_desc_edma(struct seq_file *s, struct wil6210_priv *wil,
				struct wil_ring *ring,
				char _s, char _h, int idx)
{
	u8 num_of_descs;
	bool has_skb = false;

	if (ring->is_rx) {
		struct wil_rx_enhanced_desc *rx_d =
			(struct wil_rx_enhanced_desc *)
			&ring->va[idx].rx.enhanced;
		u16 buff_id = le16_to_cpu(rx_d->mac.buff_id);

		if (wil->rx_buff_mgmt.buff_arr &&
		    wil_val_in_range(buff_id, 0, wil->rx_buff_mgmt.size))
			has_skb = wil->rx_buff_mgmt.buff_arr[buff_id].skb;
		seq_printf(s, "%c", (has_skb) ? _h : _s);
	} else {
		struct wil_tx_enhanced_desc *d =
			(struct wil_tx_enhanced_desc *)
			&ring->va[idx].tx.enhanced;

		num_of_descs = (u8)d->mac.d[2];
		has_skb = ring->ctx && ring->ctx[idx].skb;
		if (num_of_descs >= 1)
			seq_printf(s, "%c", has_skb ? _h : _s);
		else
			/* num_of_descs == 0, it's a frag in a list of descs */
			seq_printf(s, "%c", has_skb ? 'h' : _s);
	}
}