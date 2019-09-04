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
struct hns_roce_dev {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_V2_VF_ABN_INT_EN_S ; 
 int /*<<< orphan*/  HNS_ROCE_V2_VF_INT_ST_AEQ_OVERFLOW_S ; 
 int /*<<< orphan*/  HNS_ROCE_V2_VF_INT_ST_BUS_ERR_S ; 
 int /*<<< orphan*/  HNS_ROCE_V2_VF_INT_ST_OTHER_ERR_S ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  ROCEE_VF_ABN_INT_EN_REG ; 
 int /*<<< orphan*/  ROCEE_VF_ABN_INT_ST_REG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ roce_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hns_roce_v2_msix_interrupt_abn(int irq, void *dev_id)
{
	struct hns_roce_dev *hr_dev = dev_id;
	struct device *dev = hr_dev->dev;
	int int_work = 0;
	u32 int_st;
	u32 int_en;

	/* Abnormal interrupt */
	int_st = roce_read(hr_dev, ROCEE_VF_ABN_INT_ST_REG);
	int_en = roce_read(hr_dev, ROCEE_VF_ABN_INT_EN_REG);

	if (roce_get_bit(int_st, HNS_ROCE_V2_VF_INT_ST_AEQ_OVERFLOW_S)) {
		dev_err(dev, "AEQ overflow!\n");

		roce_set_bit(int_st, HNS_ROCE_V2_VF_INT_ST_AEQ_OVERFLOW_S, 1);
		roce_write(hr_dev, ROCEE_VF_ABN_INT_ST_REG, int_st);

		roce_set_bit(int_en, HNS_ROCE_V2_VF_ABN_INT_EN_S, 1);
		roce_write(hr_dev, ROCEE_VF_ABN_INT_EN_REG, int_en);

		int_work = 1;
	} else if (roce_get_bit(int_st,	HNS_ROCE_V2_VF_INT_ST_BUS_ERR_S)) {
		dev_err(dev, "BUS ERR!\n");

		roce_set_bit(int_st, HNS_ROCE_V2_VF_INT_ST_BUS_ERR_S, 1);
		roce_write(hr_dev, ROCEE_VF_ABN_INT_ST_REG, int_st);

		roce_set_bit(int_en, HNS_ROCE_V2_VF_ABN_INT_EN_S, 1);
		roce_write(hr_dev, ROCEE_VF_ABN_INT_EN_REG, int_en);

		int_work = 1;
	} else if (roce_get_bit(int_st,	HNS_ROCE_V2_VF_INT_ST_OTHER_ERR_S)) {
		dev_err(dev, "OTHER ERR!\n");

		roce_set_bit(int_st, HNS_ROCE_V2_VF_INT_ST_OTHER_ERR_S, 1);
		roce_write(hr_dev, ROCEE_VF_ABN_INT_ST_REG, int_st);

		roce_set_bit(int_en, HNS_ROCE_V2_VF_ABN_INT_EN_S, 1);
		roce_write(hr_dev, ROCEE_VF_ABN_INT_EN_REG, int_en);

		int_work = 1;
	} else
		dev_err(dev, "There is no abnormal irq found!\n");

	return IRQ_RETVAL(int_work);
}