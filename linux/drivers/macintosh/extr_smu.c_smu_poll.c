#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  db_irq; int /*<<< orphan*/  doorbell; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_READ_GPIO ; 
 int pmac_do_feature_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* smu ; 
 int /*<<< orphan*/  smu_db_intr (int /*<<< orphan*/ ,TYPE_1__*) ; 

void smu_poll(void)
{
	u8 gpio;

	if (smu == NULL)
		return;

	gpio = pmac_do_feature_call(PMAC_FTR_READ_GPIO, NULL, smu->doorbell);
	if ((gpio & 7) == 7)
		smu_db_intr(smu->db_irq, smu);
}