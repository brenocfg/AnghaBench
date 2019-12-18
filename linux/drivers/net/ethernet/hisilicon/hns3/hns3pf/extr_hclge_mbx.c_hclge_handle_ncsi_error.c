#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hnae3_ae_dev {TYPE_1__* ops; } ;
struct hclge_dev {TYPE_2__* pdev; struct hnae3_ae_dev* ae_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset_event ) (TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_default_reset_request ) (struct hnae3_ae_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_GLOBAL_RESET ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_ae_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_handle_ncsi_error(struct hclge_dev *hdev)
{
	struct hnae3_ae_dev *ae_dev = hdev->ae_dev;

	ae_dev->ops->set_default_reset_request(ae_dev, HNAE3_GLOBAL_RESET);
	dev_warn(&hdev->pdev->dev, "requesting reset due to NCSI error\n");
	ae_dev->ops->reset_event(hdev->pdev, NULL);
}