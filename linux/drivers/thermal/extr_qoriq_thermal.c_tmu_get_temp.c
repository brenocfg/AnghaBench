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
typedef  int u32 ;
struct qoriq_tmu_data {TYPE_2__* regs; } ;
struct qoriq_sensor {size_t id; struct qoriq_tmu_data* qdata; } ;
struct TYPE_4__ {TYPE_1__* site; } ;
struct TYPE_3__ {int /*<<< orphan*/  tritsr; } ;

/* Variables and functions */
 int tmu_read (struct qoriq_tmu_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tmu_get_temp(void *p, int *temp)
{
	struct qoriq_sensor *qsensor = p;
	struct qoriq_tmu_data *qdata = qsensor->qdata;
	u32 val;

	val = tmu_read(qdata, &qdata->regs->site[qsensor->id].tritsr);
	*temp = (val & 0xff) * 1000;

	return 0;
}