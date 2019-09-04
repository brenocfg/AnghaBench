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
struct TYPE_3__ {int /*<<< orphan*/  crq; int /*<<< orphan*/  csq; } ;
struct TYPE_4__ {TYPE_1__ cmq; } ;
struct hclgevf_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclgevf_free_cmd_desc (int /*<<< orphan*/ *) ; 

void hclgevf_cmd_uninit(struct hclgevf_dev *hdev)
{
	hclgevf_free_cmd_desc(&hdev->hw.cmq.csq);
	hclgevf_free_cmd_desc(&hdev->hw.cmq.crq);
}