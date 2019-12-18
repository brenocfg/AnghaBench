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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct hns_roce_v2_cmq_ring {size_t next_to_clean; size_t desc_num; struct hns_roce_cmq_desc* desc; } ;
struct TYPE_2__ {struct hns_roce_v2_cmq_ring csq; } ;
struct hns_roce_v2_priv {TYPE_1__ cmq; } ;
struct hns_roce_dev {scalar_t__ priv; } ;
struct hns_roce_cmq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROCEE_TX_CMQ_HEAD_REG ; 
 int /*<<< orphan*/  memset (struct hns_roce_cmq_desc*,int /*<<< orphan*/ ,int) ; 
 size_t roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_cmq_csq_clean(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;
	struct hns_roce_v2_cmq_ring *csq = &priv->cmq.csq;
	struct hns_roce_cmq_desc *desc;
	u16 ntc = csq->next_to_clean;
	u32 head;
	int clean = 0;

	desc = &csq->desc[ntc];
	head = roce_read(hr_dev, ROCEE_TX_CMQ_HEAD_REG);
	while (head != ntc) {
		memset(desc, 0, sizeof(*desc));
		ntc++;
		if (ntc == csq->desc_num)
			ntc = 0;
		desc = &csq->desc[ntc];
		clean++;
	}
	csq->next_to_clean = ntc;

	return clean;
}