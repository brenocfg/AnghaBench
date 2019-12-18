#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ high; scalar_t__ low; } ;
struct hclge_priv_buf {scalar_t__ buf_size; TYPE_2__ wl; scalar_t__ enable; } ;
struct hclge_pkt_buf_alloc {struct hclge_priv_buf* priv_buf; } ;
struct TYPE_3__ {unsigned int hw_pfc_map; } ;
struct hclge_dev {unsigned int hw_tc_map; TYPE_1__ tm_info; scalar_t__ pkt_buf_size; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int HCLGE_MAX_TC_NUM ; 
 int hclge_get_pfc_priv_num (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 scalar_t__ hclge_get_tx_buff_alloced (struct hclge_pkt_buf_alloc*) ; 
 int hclge_is_rx_buf_ok (struct hclge_dev*,struct hclge_pkt_buf_alloc*,scalar_t__) ; 

__attribute__((used)) static bool hclge_drop_pfc_buf_till_fit(struct hclge_dev *hdev,
					struct hclge_pkt_buf_alloc *buf_alloc)
{
	u32 rx_all = hdev->pkt_buf_size - hclge_get_tx_buff_alloced(buf_alloc);
	int pfc_priv_num = hclge_get_pfc_priv_num(hdev, buf_alloc);
	int i;

	/* let the last to be cleared first */
	for (i = HCLGE_MAX_TC_NUM - 1; i >= 0; i--) {
		struct hclge_priv_buf *priv = &buf_alloc->priv_buf[i];
		unsigned int mask = BIT((unsigned int)i);

		if (hdev->hw_tc_map & mask &&
		    hdev->tm_info.hw_pfc_map & mask) {
			/* Reduce the number of pfc TC with private buffer */
			priv->wl.low = 0;
			priv->enable = 0;
			priv->wl.high = 0;
			priv->buf_size = 0;
			pfc_priv_num--;
		}

		if (hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all) ||
		    pfc_priv_num == 0)
			break;
	}

	return hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all);
}