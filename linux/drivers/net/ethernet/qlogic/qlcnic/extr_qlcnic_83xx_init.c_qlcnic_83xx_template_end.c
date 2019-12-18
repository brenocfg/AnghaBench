#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_adapter {TYPE_3__* pdev; TYPE_2__* ahw; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int template_end; scalar_t__ seq_error; } ;
struct TYPE_5__ {TYPE_1__ reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void qlcnic_83xx_template_end(struct qlcnic_adapter *p_dev)
{
	p_dev->ahw->reset.template_end = 1;
	if (p_dev->ahw->reset.seq_error == 0)
		dev_err(&p_dev->pdev->dev,
			"HW restart process completed successfully.\n");
	else
		dev_err(&p_dev->pdev->dev,
			"HW restart completed with timeout errors.\n");
}