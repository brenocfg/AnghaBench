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
struct dvb_frontend {TYPE_1__* dvb; } ;
struct budget {int dummy; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_2__ {scalar_t__ priv; } ;

/* Variables and functions */
 int SetVoltage_Activy (struct budget*,int) ; 

__attribute__((used)) static int siemens_budget_set_voltage(struct dvb_frontend *fe,
				      enum fe_sec_voltage voltage)
{
	struct budget* budget = (struct budget*) fe->dvb->priv;

	return SetVoltage_Activy (budget, voltage);
}