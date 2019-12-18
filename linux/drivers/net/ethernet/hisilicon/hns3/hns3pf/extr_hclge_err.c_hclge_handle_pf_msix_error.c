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
struct hclge_desc {int /*<<< orphan*/ * data; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int HCLGE_PPU_PF_INT_MSIX_MASK ; 
 int HCLGE_PPU_PF_OVER_8BD_ERR_MASK ; 
 int /*<<< orphan*/  HCLGE_QUERY_CLEAR_ALL_PF_MSIX_INT ; 
 int HCLGE_SSU_PORT_INT_MSIX_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int hclge_clear_hw_msix_error (struct hclge_dev*,struct hclge_desc*,int,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hclge_handle_over_8bd_err (struct hclge_dev*,unsigned long*) ; 
 int /*<<< orphan*/  hclge_log_error (struct device*,char*,int /*<<< orphan*/ *,int,unsigned long*) ; 
 int /*<<< orphan*/ * hclge_ppp_pf_abnormal_int ; 
 int /*<<< orphan*/ * hclge_ppu_pf_abnormal_int ; 
 int /*<<< orphan*/ * hclge_ssu_port_based_pf_int ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_handle_pf_msix_error(struct hclge_dev *hdev,
				      struct hclge_desc *desc,
				      int pf_bd_num,
				      unsigned long *reset_requests)
{
	struct device *dev = &hdev->pdev->dev;
	__le32 *desc_data;
	u32 status;
	int ret;

	/* query all PF MSIx errors */
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_QUERY_CLEAR_ALL_PF_MSIX_INT,
				   true);
	ret = hclge_cmd_send(&hdev->hw, &desc[0], pf_bd_num);
	if (ret) {
		dev_err(dev, "query all pf msix int cmd failed (%d)\n", ret);
		return ret;
	}

	/* log SSU PF errors */
	status = le32_to_cpu(desc[0].data[0]) & HCLGE_SSU_PORT_INT_MSIX_MASK;
	if (status)
		hclge_log_error(dev, "SSU_PORT_BASED_ERR_INT",
				&hclge_ssu_port_based_pf_int[0],
				status, reset_requests);

	/* read and log PPP PF errors */
	desc_data = (__le32 *)&desc[2];
	status = le32_to_cpu(*desc_data);
	if (status)
		hclge_log_error(dev, "PPP_PF_ABNORMAL_INT_ST0",
				&hclge_ppp_pf_abnormal_int[0],
				status, reset_requests);

	/* log PPU(RCB) PF errors */
	desc_data = (__le32 *)&desc[3];
	status = le32_to_cpu(*desc_data) & HCLGE_PPU_PF_INT_MSIX_MASK;
	if (status)
		hclge_log_error(dev, "PPU_PF_ABNORMAL_INT_ST",
				&hclge_ppu_pf_abnormal_int[0],
				status, reset_requests);

	status = le32_to_cpu(*desc_data) & HCLGE_PPU_PF_OVER_8BD_ERR_MASK;
	if (status)
		hclge_handle_over_8bd_err(hdev, reset_requests);

	/* clear all PF MSIx errors */
	ret = hclge_clear_hw_msix_error(hdev, desc, false, pf_bd_num);
	if (ret)
		dev_err(dev, "clear all pf msix int cmd failed (%d)\n", ret);

	return ret;
}