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
 int /*<<< orphan*/  HCLGEVF_VECTOR0_CMDQ_SRC_REG ; 
 int /*<<< orphan*/  hclgevf_write_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclgevf_clear_event_cause(struct hclgevf_dev *hdev, u32 regclr)
{
	hclgevf_write_dev(&hdev->hw, HCLGEVF_VECTOR0_CMDQ_SRC_REG, regclr);
}