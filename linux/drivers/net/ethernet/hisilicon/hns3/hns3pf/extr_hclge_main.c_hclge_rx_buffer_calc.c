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
typedef  int /*<<< orphan*/  u32 ;
struct hclge_pkt_buf_alloc {int dummy; } ;
struct hclge_dev {int /*<<< orphan*/  pkt_buf_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ hclge_drop_nopfc_buf_till_fit (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 scalar_t__ hclge_drop_pfc_buf_till_fit (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 scalar_t__ hclge_get_tx_buff_alloced (struct hclge_pkt_buf_alloc*) ; 
 int /*<<< orphan*/  hclge_is_rx_buf_ok (struct hclge_dev*,struct hclge_pkt_buf_alloc*,int /*<<< orphan*/ ) ; 
 scalar_t__ hclge_only_alloc_priv_buff (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 scalar_t__ hclge_rx_buf_calc_all (struct hclge_dev*,int,struct hclge_pkt_buf_alloc*) ; 
 int /*<<< orphan*/  hnae3_dev_dcb_supported (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_rx_buffer_calc(struct hclge_dev *hdev,
				struct hclge_pkt_buf_alloc *buf_alloc)
{
	/* When DCB is not supported, rx private buffer is not allocated. */
	if (!hnae3_dev_dcb_supported(hdev)) {
		u32 rx_all = hdev->pkt_buf_size;

		rx_all -= hclge_get_tx_buff_alloced(buf_alloc);
		if (!hclge_is_rx_buf_ok(hdev, buf_alloc, rx_all))
			return -ENOMEM;

		return 0;
	}

	if (hclge_only_alloc_priv_buff(hdev, buf_alloc))
		return 0;

	if (hclge_rx_buf_calc_all(hdev, true, buf_alloc))
		return 0;

	/* try to decrease the buffer size */
	if (hclge_rx_buf_calc_all(hdev, false, buf_alloc))
		return 0;

	if (hclge_drop_nopfc_buf_till_fit(hdev, buf_alloc))
		return 0;

	if (hclge_drop_pfc_buf_till_fit(hdev, buf_alloc))
		return 0;

	return -ENOMEM;
}