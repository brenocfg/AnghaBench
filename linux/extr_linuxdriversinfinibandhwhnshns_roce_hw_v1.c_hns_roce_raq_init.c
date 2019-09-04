#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hns_roce_raq_table {TYPE_2__* e_raq_buf; } ;
struct hns_roce_v1_priv {struct hns_roce_raq_table raq_table; } ;
struct hns_roce_dev {scalar_t__ priv; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_5__ {int map; int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HNS_ROCE_V1_EXT_RAQ_WF ; 
 int HNS_ROCE_V1_RAQ_ENTRY ; 
 int HNS_ROCE_V1_RAQ_SIZE ; 
 int POL_TIME_INTERVAL_VAL ; 
 int /*<<< orphan*/  ROCEE_EXT_RAQ_H_EXT_RAQ_BA_H_M ; 
 int /*<<< orphan*/  ROCEE_EXT_RAQ_H_EXT_RAQ_BA_H_S ; 
 int /*<<< orphan*/  ROCEE_EXT_RAQ_H_EXT_RAQ_SHIFT_M ; 
 int /*<<< orphan*/  ROCEE_EXT_RAQ_H_EXT_RAQ_SHIFT_S ; 
 int /*<<< orphan*/  ROCEE_EXT_RAQ_H_REG ; 
 int /*<<< orphan*/  ROCEE_EXT_RAQ_REG ; 
 int /*<<< orphan*/  ROCEE_GLB_CFG_REG ; 
 int /*<<< orphan*/  ROCEE_GLB_CFG_TRP_RAQ_DROP_EN_S ; 
 int /*<<< orphan*/  ROCEE_RAQ_WL_REG ; 
 int /*<<< orphan*/  ROCEE_RAQ_WL_ROCEE_RAQ_WL_M ; 
 int /*<<< orphan*/  ROCEE_RAQ_WL_ROCEE_RAQ_WL_S ; 
 int /*<<< orphan*/  ROCEE_WRMS_POL_TIME_INTERVAL_REG ; 
 int /*<<< orphan*/  ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_EXT_RAQ_MODE ; 
 int /*<<< orphan*/  ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_POL_TIME_INTERVAL_M ; 
 int /*<<< orphan*/  ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_POL_TIME_INTERVAL_S ; 
 int /*<<< orphan*/  ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_CFG_M ; 
 int /*<<< orphan*/  ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_CFG_S ; 
 int /*<<< orphan*/  ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_EN_S ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int*,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hns_roce_raq_init(struct hns_roce_dev *hr_dev)
{
	int ret;
	u32 val;
	__le32 tmp;
	int raq_shift = 0;
	dma_addr_t addr;
	struct hns_roce_v1_priv *priv;
	struct hns_roce_raq_table *raq;
	struct device *dev = &hr_dev->pdev->dev;

	priv = (struct hns_roce_v1_priv *)hr_dev->priv;
	raq = &priv->raq_table;

	raq->e_raq_buf = kzalloc(sizeof(*(raq->e_raq_buf)), GFP_KERNEL);
	if (!raq->e_raq_buf)
		return -ENOMEM;

	raq->e_raq_buf->buf = dma_alloc_coherent(dev, HNS_ROCE_V1_RAQ_SIZE,
						 &addr, GFP_KERNEL);
	if (!raq->e_raq_buf->buf) {
		ret = -ENOMEM;
		goto err_dma_alloc_raq;
	}
	raq->e_raq_buf->map = addr;

	/* Configure raq extended address. 48bit 4K align*/
	roce_write(hr_dev, ROCEE_EXT_RAQ_REG, raq->e_raq_buf->map >> 12);

	/* Configure raq_shift */
	raq_shift = ilog2(HNS_ROCE_V1_RAQ_SIZE / HNS_ROCE_V1_RAQ_ENTRY);
	val = roce_read(hr_dev, ROCEE_EXT_RAQ_H_REG);
	tmp = cpu_to_le32(val);
	roce_set_field(tmp, ROCEE_EXT_RAQ_H_EXT_RAQ_SHIFT_M,
		       ROCEE_EXT_RAQ_H_EXT_RAQ_SHIFT_S, raq_shift);
	/*
	 * 44 = 32 + 12, When evaluating addr to hardware, shift 12 because of
	 * using 4K page, and shift more 32 because of
	 * caculating the high 32 bit value evaluated to hardware.
	 */
	roce_set_field(tmp, ROCEE_EXT_RAQ_H_EXT_RAQ_BA_H_M,
		       ROCEE_EXT_RAQ_H_EXT_RAQ_BA_H_S,
		       raq->e_raq_buf->map >> 44);
	val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_EXT_RAQ_H_REG, val);
	dev_dbg(dev, "Configure raq_shift 0x%x.\n", val);

	/* Configure raq threshold */
	val = roce_read(hr_dev, ROCEE_RAQ_WL_REG);
	tmp = cpu_to_le32(val);
	roce_set_field(tmp, ROCEE_RAQ_WL_ROCEE_RAQ_WL_M,
		       ROCEE_RAQ_WL_ROCEE_RAQ_WL_S,
		       HNS_ROCE_V1_EXT_RAQ_WF);
	val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_RAQ_WL_REG, val);
	dev_dbg(dev, "Configure raq_wl 0x%x.\n", val);

	/* Enable extend raq */
	val = roce_read(hr_dev, ROCEE_WRMS_POL_TIME_INTERVAL_REG);
	tmp = cpu_to_le32(val);
	roce_set_field(tmp,
		       ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_POL_TIME_INTERVAL_M,
		       ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_POL_TIME_INTERVAL_S,
		       POL_TIME_INTERVAL_VAL);
	roce_set_bit(tmp, ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_EXT_RAQ_MODE, 1);
	roce_set_field(tmp,
		       ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_CFG_M,
		       ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_CFG_S,
		       2);
	roce_set_bit(tmp,
		     ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_EN_S, 1);
	val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_WRMS_POL_TIME_INTERVAL_REG, val);
	dev_dbg(dev, "Configure WrmsPolTimeInterval 0x%x.\n", val);

	/* Enable raq drop */
	val = roce_read(hr_dev, ROCEE_GLB_CFG_REG);
	tmp = cpu_to_le32(val);
	roce_set_bit(tmp, ROCEE_GLB_CFG_TRP_RAQ_DROP_EN_S, 1);
	val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_GLB_CFG_REG, val);
	dev_dbg(dev, "Configure GlbCfg = 0x%x.\n", val);

	return 0;

err_dma_alloc_raq:
	kfree(raq->e_raq_buf);
	return ret;
}