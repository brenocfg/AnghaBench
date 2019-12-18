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
struct hnae3_handle {TYPE_1__* pdev; } ;
typedef  enum hnae3_hw_error_type { ____Placeholder_hnae3_hw_error_type } hnae3_hw_error_type ;
struct TYPE_5__ {int type; int /*<<< orphan*/  msg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* hns3_hw_err ; 

__attribute__((used)) static void hns3_process_hw_error(struct hnae3_handle *handle,
				  enum hnae3_hw_error_type type)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(hns3_hw_err); i++) {
		if (hns3_hw_err[i].type == type) {
			dev_err(&handle->pdev->dev, "Detected %s!\n",
				hns3_hw_err[i].msg);
			break;
		}
	}
}