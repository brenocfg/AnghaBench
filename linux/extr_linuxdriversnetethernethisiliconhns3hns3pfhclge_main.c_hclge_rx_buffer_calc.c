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
struct TYPE_4__ {int low; int high; } ;
struct hclge_priv_buf {int enable; int buf_size; TYPE_2__ wl; } ;
struct hclge_pkt_buf_alloc {struct hclge_priv_buf* priv_buf; } ;
struct TYPE_3__ {int hw_pfc_map; } ;
struct hclge_dev {int pkt_buf_size; int hw_tc_map; TYPE_1__ tm_info; int /*<<< orphan*/  mps; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ENOMEM ; 
 void* HCLGE_DEFAULT_DV ; 
 int HCLGE_MAX_TC_NUM ; 
 int hclge_get_no_pfc_priv_num (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 int hclge_get_pfc_priv_num (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 scalar_t__ hclge_get_tx_buff_alloced (struct hclge_pkt_buf_alloc*) ; 
 scalar_t__ hclge_is_rx_buf_ok (struct hclge_dev*,struct hclge_pkt_buf_alloc*,int) ; 
 int /*<<< orphan*/  hnae3_dev_dcb_supported (struct hclge_dev*) ; 
 int round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_rx_buffer_calc(struct hclge_dev *hdev,
				struct hclge_pkt_buf_alloc *buf_alloc)
{
#define HCLGE_BUF_SIZE_UNIT	128
	u32 rx_all = hdev->pkt_buf_size, aligned_mps;
	int no_pfc_priv_num, pfc_priv_num;
	struct hclge_priv_buf *priv;
	int i;

	aligned_mps = round_up(hdev->mps, HCLGE_BUF_SIZE_UNIT);
	rx_all -= hclge_get_tx_buff_alloced(buf_alloc);

	/* When DCB is not supported, rx private
	 * buffer is not allocated.
	 */
	if (!hnae3_dev_dcb_supported(hdev)) {
		if (!hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all))
			return -ENOMEM;

		return 0;
	}

	/* step 1, try to alloc private buffer for all enabled tc */
	for (i = 0; i < HCLGE_MAX_TC_NUM; i++) {
		priv = &buf_alloc->priv_buf[i];
		if (hdev->hw_tc_map & BIT(i)) {
			priv->enable = 1;
			if (hdev->tm_info.hw_pfc_map & BIT(i)) {
				priv->wl.low = aligned_mps;
				priv->wl.high = priv->wl.low + aligned_mps;
				priv->buf_size = priv->wl.high +
						HCLGE_DEFAULT_DV;
			} else {
				priv->wl.low = 0;
				priv->wl.high = 2 * aligned_mps;
				priv->buf_size = priv->wl.high;
			}
		} else {
			priv->enable = 0;
			priv->wl.low = 0;
			priv->wl.high = 0;
			priv->buf_size = 0;
		}
	}

	if (hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all))
		return 0;

	/* step 2, try to decrease the buffer size of
	 * no pfc TC's private buffer
	 */
	for (i = 0; i < HCLGE_MAX_TC_NUM; i++) {
		priv = &buf_alloc->priv_buf[i];

		priv->enable = 0;
		priv->wl.low = 0;
		priv->wl.high = 0;
		priv->buf_size = 0;

		if (!(hdev->hw_tc_map & BIT(i)))
			continue;

		priv->enable = 1;

		if (hdev->tm_info.hw_pfc_map & BIT(i)) {
			priv->wl.low = 128;
			priv->wl.high = priv->wl.low + aligned_mps;
			priv->buf_size = priv->wl.high + HCLGE_DEFAULT_DV;
		} else {
			priv->wl.low = 0;
			priv->wl.high = aligned_mps;
			priv->buf_size = priv->wl.high;
		}
	}

	if (hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all))
		return 0;

	/* step 3, try to reduce the number of pfc disabled TCs,
	 * which have private buffer
	 */
	/* get the total no pfc enable TC number, which have private buffer */
	no_pfc_priv_num = hclge_get_no_pfc_priv_num(hdev, buf_alloc);

	/* let the last to be cleared first */
	for (i = HCLGE_MAX_TC_NUM - 1; i >= 0; i--) {
		priv = &buf_alloc->priv_buf[i];

		if (hdev->hw_tc_map & BIT(i) &&
		    !(hdev->tm_info.hw_pfc_map & BIT(i))) {
			/* Clear the no pfc TC private buffer */
			priv->wl.low = 0;
			priv->wl.high = 0;
			priv->buf_size = 0;
			priv->enable = 0;
			no_pfc_priv_num--;
		}

		if (hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all) ||
		    no_pfc_priv_num == 0)
			break;
	}

	if (hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all))
		return 0;

	/* step 4, try to reduce the number of pfc enabled TCs
	 * which have private buffer.
	 */
	pfc_priv_num = hclge_get_pfc_priv_num(hdev, buf_alloc);

	/* let the last to be cleared first */
	for (i = HCLGE_MAX_TC_NUM - 1; i >= 0; i--) {
		priv = &buf_alloc->priv_buf[i];

		if (hdev->hw_tc_map & BIT(i) &&
		    hdev->tm_info.hw_pfc_map & BIT(i)) {
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
	if (hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all))
		return 0;

	return -ENOMEM;
}