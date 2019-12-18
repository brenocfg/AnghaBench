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
struct hclgevf_dev {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_NIC_CSQ_DEPTH_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_SW_RST_RDY ; 
 int /*<<< orphan*/  hclgevf_read_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclgevf_write_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclgevf_reset_handshake(struct hclgevf_dev *hdev, bool enable)
{
	u32 reg_val;

	reg_val = hclgevf_read_dev(&hdev->hw, HCLGEVF_NIC_CSQ_DEPTH_REG);
	if (enable)
		reg_val |= HCLGEVF_NIC_SW_RST_RDY;
	else
		reg_val &= ~HCLGEVF_NIC_SW_RST_RDY;

	hclgevf_write_dev(&hdev->hw, HCLGEVF_NIC_CSQ_DEPTH_REG,
			  reg_val);
}