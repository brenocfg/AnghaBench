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
typedef  int /*<<< orphan*/  u32 ;
struct hns_roce_dev {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_PORT_UP ; 
 int PAGES_SHIFT_16 ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG1_REG ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG1_ROCEE_CACHE_TB_CFG_M ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG1_ROCEE_CACHE_TB_CFG_S ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG1_ROCEE_STREAM_ID_TB_CFG_M ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG1_ROCEE_STREAM_ID_TB_CFG_S ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG2_REG ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG2_ROCEE_CACHE_PKT_CFG_M ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG2_ROCEE_CACHE_PKT_CFG_S ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG2_ROCEE_STREAM_ID_PKT_CFG_M ; 
 int /*<<< orphan*/  ROCEE_DMAE_USER_CFG2_ROCEE_STREAM_ID_PKT_CFG_S ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  hns_roce_bt_free (struct hns_roce_dev*) ; 
 int hns_roce_bt_init (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_db_free (struct hns_roce_dev*) ; 
 int hns_roce_db_init (struct hns_roce_dev*) ; 
 int hns_roce_free_mr_init (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_port_enable (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_raq_free (struct hns_roce_dev*) ; 
 int hns_roce_raq_init (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_tptr_free (struct hns_roce_dev*) ; 
 int hns_roce_tptr_init (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_read (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_v1_init(struct hns_roce_dev *hr_dev)
{
	int ret;
	u32 val;
	__le32 tmp;
	struct device *dev = &hr_dev->pdev->dev;

	/* DMAE user config */
	val = roce_read(hr_dev, ROCEE_DMAE_USER_CFG1_REG);
	tmp = cpu_to_le32(val);
	roce_set_field(tmp, ROCEE_DMAE_USER_CFG1_ROCEE_CACHE_TB_CFG_M,
		       ROCEE_DMAE_USER_CFG1_ROCEE_CACHE_TB_CFG_S, 0xf);
	roce_set_field(tmp, ROCEE_DMAE_USER_CFG1_ROCEE_STREAM_ID_TB_CFG_M,
		       ROCEE_DMAE_USER_CFG1_ROCEE_STREAM_ID_TB_CFG_S,
		       1 << PAGES_SHIFT_16);
	val = le32_to_cpu(tmp);
	roce_write(hr_dev, ROCEE_DMAE_USER_CFG1_REG, val);

	val = roce_read(hr_dev, ROCEE_DMAE_USER_CFG2_REG);
	tmp = cpu_to_le32(val);
	roce_set_field(tmp, ROCEE_DMAE_USER_CFG2_ROCEE_CACHE_PKT_CFG_M,
		       ROCEE_DMAE_USER_CFG2_ROCEE_CACHE_PKT_CFG_S, 0xf);
	roce_set_field(tmp, ROCEE_DMAE_USER_CFG2_ROCEE_STREAM_ID_PKT_CFG_M,
		       ROCEE_DMAE_USER_CFG2_ROCEE_STREAM_ID_PKT_CFG_S,
		       1 << PAGES_SHIFT_16);

	ret = hns_roce_db_init(hr_dev);
	if (ret) {
		dev_err(dev, "doorbell init failed!\n");
		return ret;
	}

	ret = hns_roce_raq_init(hr_dev);
	if (ret) {
		dev_err(dev, "raq init failed!\n");
		goto error_failed_raq_init;
	}

	ret = hns_roce_bt_init(hr_dev);
	if (ret) {
		dev_err(dev, "bt init failed!\n");
		goto error_failed_bt_init;
	}

	ret = hns_roce_tptr_init(hr_dev);
	if (ret) {
		dev_err(dev, "tptr init failed!\n");
		goto error_failed_tptr_init;
	}

	ret = hns_roce_free_mr_init(hr_dev);
	if (ret) {
		dev_err(dev, "free mr init failed!\n");
		goto error_failed_free_mr_init;
	}

	hns_roce_port_enable(hr_dev, HNS_ROCE_PORT_UP);

	return 0;

error_failed_free_mr_init:
	hns_roce_tptr_free(hr_dev);

error_failed_tptr_init:
	hns_roce_bt_free(hr_dev);

error_failed_bt_init:
	hns_roce_raq_free(hr_dev);

error_failed_raq_init:
	hns_roce_db_free(hr_dev);
	return ret;
}