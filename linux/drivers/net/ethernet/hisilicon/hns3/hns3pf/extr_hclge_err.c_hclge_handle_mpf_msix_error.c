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
struct hclge_dev {int /*<<< orphan*/  hw; TYPE_1__* pdev; } ;
struct hclge_desc {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int HCLGE_PPU_MPF_INT_ST2_MSIX_MASK ; 
 int /*<<< orphan*/  HCLGE_QUERY_CLEAR_ALL_MPF_MSIX_INT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int hclge_clear_hw_msix_error (struct hclge_dev*,struct hclge_desc*,int,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hclge_log_error (struct device*,char*,int /*<<< orphan*/ *,int,unsigned long*) ; 
 int /*<<< orphan*/ * hclge_mac_afifo_tnl_int ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_handle_mpf_msix_error(struct hclge_dev *hdev,
				       struct hclge_desc *desc,
				       int mpf_bd_num,
				       unsigned long *reset_requests)
{
	struct device *dev = &hdev->pdev->dev;
	__le32 *desc_data;
	u32 status;
	int ret;
	/* query all main PF MSIx errors */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_QUERY_CLEAR_ALL_MPF_MSIX_INT,
				   true);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], mpf_bd_num);
	if (ret) {
		dev_err(dev, "query all mpf msix int cmd failed (%d)\n", ret);
		return ret;
	}

	/* log MAC errors */
	desc_data = (__le32 *)&desc[1];
	status = le32_to_cpu(*desc_data);
	if (status)
		hclge_log_error(dev, "MAC_AFIFO_TNL_INT_R",
				&hclge_mac_afifo_tnl_int[0], status,
				reset_requests);

	/* log PPU(RCB) MPF errors */
	desc_data = (__le32 *)&desc[5];
	status = le32_to_cpu(*(desc_data + 2)) &
			HCLGE_PPU_MPF_INT_ST2_MSIX_MASK;
	if (status)
		dev_err(dev, "PPU_MPF_ABNORMAL_INT_ST2 rx_q_search_miss found [dfx status=0x%x\n]",
			status);

	/* clear all main PF MSIx errors */
	ret = hclge_clear_hw_msix_error(hdev, desc, true, mpf_bd_num);
	if (ret)
		dev_err(dev, "clear all mpf msix int cmd failed (%d)\n", ret);

	return ret;
}