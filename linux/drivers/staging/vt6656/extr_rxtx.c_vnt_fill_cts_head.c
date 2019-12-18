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
struct TYPE_2__ {int /*<<< orphan*/  ra; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  duration; } ;
struct vnt_cts {int /*<<< orphan*/  data_head; TYPE_1__ data; int /*<<< orphan*/  duration_ba; int /*<<< orphan*/  b; } ;
union vnt_tx_data_head {struct vnt_cts cts_g; } ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_usb_send_context {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  tx_rate; struct vnt_private* priv; } ;
struct vnt_private {int /*<<< orphan*/  current_net_addr; int /*<<< orphan*/  top_cck_basic_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTSDUR_BA ; 
 int IEEE80211_FTYPE_CTL ; 
 int IEEE80211_STYPE_CTS ; 
 int /*<<< orphan*/  PK_TYPE_11B ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_get_phy_field (struct vnt_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_get_rtscts_duration_le (struct vnt_usb_send_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_rxtx_datahead_g (struct vnt_usb_send_context*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 vnt_fill_cts_head(struct vnt_usb_send_context *tx_context,
			     union vnt_tx_data_head *head)
{
	struct vnt_private *priv = tx_context->priv;
	struct vnt_cts *buf = &head->cts_g;
	u32 cts_frame_len = 14;
	u16 current_rate = tx_context->tx_rate;

	/* Get SignalField,ServiceField,Length */
	vnt_get_phy_field(priv, cts_frame_len, priv->top_cck_basic_rate,
			  PK_TYPE_11B, &buf->b);
	/* Get CTSDuration_ba */
	buf->duration_ba =
		vnt_get_rtscts_duration_le(tx_context, CTSDUR_BA,
					   tx_context->pkt_type,
					   current_rate);
	/*Get CTS Frame body*/
	buf->data.duration = buf->duration_ba;
	buf->data.frame_control =
		cpu_to_le16(IEEE80211_FTYPE_CTL | IEEE80211_STYPE_CTS);

	ether_addr_copy(buf->data.ra, priv->current_net_addr);

	return vnt_rxtx_datahead_g(tx_context, &buf->data_head);
}