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
struct hclge_priv_buf {scalar_t__ enable; } ;
struct hclge_pkt_buf_alloc {struct hclge_priv_buf* priv_buf; } ;
struct TYPE_2__ {int hw_pfc_map; } ;
struct hclge_dev {TYPE_1__ tm_info; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 unsigned int HCLGE_MAX_TC_NUM ; 

__attribute__((used)) static int hclge_get_pfc_priv_num(struct hclge_dev *hdev,
				  struct hclge_pkt_buf_alloc *buf_alloc)
{
	struct hclge_priv_buf *priv;
	unsigned int i;
	int cnt = 0;

	for (i = 0; i < HCLGE_MAX_TC_NUM; i++) {
		priv = &buf_alloc->priv_buf[i];
		if ((hdev->tm_info.hw_pfc_map & BIT(i)) &&
		    priv->enable)
			cnt++;
	}

	return cnt;
}