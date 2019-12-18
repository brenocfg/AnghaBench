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
struct hnae3_ae_dev {int /*<<< orphan*/  hw_err_reset_req; struct hclge_dev* priv; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  state; } ;
typedef  enum hnae3_reset_type { ____Placeholder_hnae3_reset_type } hnae3_reset_type ;
struct TYPE_2__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_STATE_RST_HANDLING ; 
 int HNAE3_NONE_RESET ; 
 int hclge_log_and_clear_rocee_ras_error (struct hclge_dev*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_handle_rocee_ras_error(struct hnae3_ae_dev *ae_dev)
{
	struct hclge_dev *hdev = ae_dev->priv;
	enum hnae3_reset_type reset_type;

	if (test_bit(HCLGE_STATE_RST_HANDLING, &hdev->state) ||
	    hdev->pdev->revision < 0x21)
		return;

	reset_type = hclge_log_and_clear_rocee_ras_error(hdev);
	if (reset_type != HNAE3_NONE_RESET)
		set_bit(reset_type, &ae_dev->hw_err_reset_req);
}