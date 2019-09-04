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
typedef  int uint32_t ;
struct ve_spc_drvdata {int /*<<< orphan*/  done; scalar_t__ baseaddr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int cur_rsp_mask; int cur_rsp_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PWC_STATUS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 TYPE_1__* info ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static irqreturn_t ve_spc_irq_handler(int irq, void *data)
{
	struct ve_spc_drvdata *drv_data = data;
	uint32_t status = readl_relaxed(drv_data->baseaddr + PWC_STATUS);

	if (info->cur_rsp_mask & status) {
		info->cur_rsp_stat = status;
		complete(&drv_data->done);
	}

	return IRQ_HANDLED;
}