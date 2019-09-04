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
struct hclgevf_cmq_ring {size_t next_to_clean; size_t desc_num; struct hclgevf_desc* desc; } ;
struct TYPE_2__ {struct hclgevf_cmq_ring csq; } ;
struct hclgevf_hw {TYPE_1__ cmq; } ;
struct hclgevf_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_NIC_CSQ_HEAD_REG ; 
 size_t hclgevf_read_dev (struct hclgevf_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hclgevf_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclgevf_cmd_csq_clean(struct hclgevf_hw *hw)
{
	struct hclgevf_cmq_ring *csq = &hw->cmq.csq;
	u16 ntc = csq->next_to_clean;
	struct hclgevf_desc *desc;
	int clean = 0;
	u32 head;

	desc = &csq->desc[ntc];
	head = hclgevf_read_dev(hw, HCLGEVF_NIC_CSQ_HEAD_REG);
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