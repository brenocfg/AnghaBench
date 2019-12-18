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
struct budget {TYPE_2__* dvb_frontend; scalar_t__ read_fe_status; } ;
struct TYPE_3__ {scalar_t__ read_status; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 scalar_t__ budget_read_fe_status ; 

void ttpci_budget_init_hooks(struct budget *budget)
{
	if (budget->dvb_frontend && !budget->read_fe_status) {
		budget->read_fe_status = budget->dvb_frontend->ops.read_status;
		budget->dvb_frontend->ops.read_status = budget_read_fe_status;
	}
}