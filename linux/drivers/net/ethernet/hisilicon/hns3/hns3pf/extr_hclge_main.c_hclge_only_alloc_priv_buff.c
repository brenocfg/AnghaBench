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
typedef  int u32 ;
struct TYPE_3__ {int low; int high; } ;
struct hclge_priv_buf {int enable; int buf_size; TYPE_1__ wl; } ;
struct TYPE_4__ {scalar_t__ buf_size; } ;
struct hclge_pkt_buf_alloc {TYPE_2__ s_buf; struct hclge_priv_buf* priv_buf; } ;
struct hclge_dev {int pkt_buf_size; int mps; int dv_buf_size; int hw_tc_map; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int BUF_MAX_PERCENT ; 
 int BUF_RESERVE_PERCENT ; 
 int COMPENSATE_BUFFER ; 
 int COMPENSATE_HALF_MPS_NUM ; 
 int /*<<< orphan*/  HCLGE_BUF_SIZE_UNIT ; 
 unsigned int HCLGE_MAX_TC_NUM ; 
 int NEED_RESERVE_TC_NUM ; 
 int PRIV_WL_GAP ; 
 int hclge_get_tc_num (struct hclge_dev*) ; 
 int hclge_get_tx_buff_alloced (struct hclge_pkt_buf_alloc*) ; 
 int round_down (int,int /*<<< orphan*/ ) ; 
 int round_up (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_only_alloc_priv_buff(struct hclge_dev *hdev,
				      struct hclge_pkt_buf_alloc *buf_alloc)
{
#define COMPENSATE_BUFFER	0x3C00
#define COMPENSATE_HALF_MPS_NUM	5
#define PRIV_WL_GAP		0x1800

	u32 rx_priv = hdev->pkt_buf_size - hclge_get_tx_buff_alloced(buf_alloc);
	u32 tc_num = hclge_get_tc_num(hdev);
	u32 half_mps = hdev->mps >> 1;
	u32 min_rx_priv;
	unsigned int i;

	if (tc_num)
		rx_priv = rx_priv / tc_num;

	if (tc_num <= NEED_RESERVE_TC_NUM)
		rx_priv = rx_priv * BUF_RESERVE_PERCENT / BUF_MAX_PERCENT;

	min_rx_priv = hdev->dv_buf_size + COMPENSATE_BUFFER +
			COMPENSATE_HALF_MPS_NUM * half_mps;
	min_rx_priv = round_up(min_rx_priv, HCLGE_BUF_SIZE_UNIT);
	rx_priv = round_down(rx_priv, HCLGE_BUF_SIZE_UNIT);

	if (rx_priv < min_rx_priv)
		return false;

	for (i = 0; i < HCLGE_MAX_TC_NUM; i++) {
		struct hclge_priv_buf *priv = &buf_alloc->priv_buf[i];

		priv->enable = 0;
		priv->wl.low = 0;
		priv->wl.high = 0;
		priv->buf_size = 0;

		if (!(hdev->hw_tc_map & BIT(i)))
			continue;

		priv->enable = 1;
		priv->buf_size = rx_priv;
		priv->wl.high = rx_priv - hdev->dv_buf_size;
		priv->wl.low = priv->wl.high - PRIV_WL_GAP;
	}

	buf_alloc->s_buf.buf_size = 0;

	return true;
}