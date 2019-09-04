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
typedef  int u32 ;
struct TYPE_2__ {int num_comp_vectors; } ;
struct hns_roce_dev {TYPE_1__ caps; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CEQ_REG_OFFSET ; 
 int /*<<< orphan*/  ROCEE_CAEP_AE_MASK_CAEP_AEQ_ALM_OVF_MASK_S ; 
 int /*<<< orphan*/  ROCEE_CAEP_AE_MASK_CAEP_AE_IRQ_MASK_S ; 
 scalar_t__ ROCEE_CAEP_AE_MASK_REG ; 
 scalar_t__ ROCEE_CAEP_CE_IRQ_MASK_0_REG ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int roce_read (struct hns_roce_dev*,scalar_t__) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,scalar_t__,int) ; 

__attribute__((used)) static void hns_roce_v1_int_mask_enable(struct hns_roce_dev *hr_dev)
{
	u32 aemask_val;
	int masken = 0;
	__le32 tmp;
	int i;

	/* AEQ INT */
	aemask_val = roce_read(hr_dev, ROCEE_CAEP_AE_MASK_REG);
	tmp = cpu_to_le32(aemask_val);
	roce_set_bit(tmp, ROCEE_CAEP_AE_MASK_CAEP_AEQ_ALM_OVF_MASK_S,
		     masken);
	roce_set_bit(tmp, ROCEE_CAEP_AE_MASK_CAEP_AE_IRQ_MASK_S, masken);
	aemask_val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_CAEP_AE_MASK_REG, aemask_val);

	/* CEQ INT */
	for (i = 0; i < hr_dev->caps.num_comp_vectors; i++) {
		/* IRQ mask */
		roce_write(hr_dev, ROCEE_CAEP_CE_IRQ_MASK_0_REG +
			   i * CEQ_REG_OFFSET, masken);
	}
}