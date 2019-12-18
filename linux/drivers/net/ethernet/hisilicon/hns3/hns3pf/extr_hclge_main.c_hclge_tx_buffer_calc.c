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
typedef  size_t u32 ;
struct hclge_priv_buf {size_t tx_buf_size; } ;
struct hclge_pkt_buf_alloc {struct hclge_priv_buf* priv_buf; } ;
struct hclge_dev {size_t pkt_buf_size; int hw_tc_map; size_t tx_buf_size; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int ENOMEM ; 
 size_t HCLGE_MAX_TC_NUM ; 

__attribute__((used)) static int hclge_tx_buffer_calc(struct hclge_dev *hdev,
				struct hclge_pkt_buf_alloc *buf_alloc)
{
	u32 i, total_size;

	total_size = hdev->pkt_buf_size;

	/* alloc tx buffer for all enabled tc */
	for (i = 0; i < HCLGE_MAX_TC_NUM; i++) {
		struct hclge_priv_buf *priv = &buf_alloc->priv_buf[i];

		if (hdev->hw_tc_map & BIT(i)) {
			if (total_size < hdev->tx_buf_size)
				return -ENOMEM;

			priv->tx_buf_size = hdev->tx_buf_size;
		} else {
			priv->tx_buf_size = 0;
		}

		total_size -= priv->tx_buf_size;
	}

	return 0;
}