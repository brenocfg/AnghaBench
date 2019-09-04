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
struct cx88_core {int (* prev_set_voltage ) (struct dvb_frontend*,int) ;} ;
struct cx8802_dev {struct cx88_core* core; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_2__ {struct cx8802_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_GP0_IO ; 
 int SEC_VOLTAGE_OFF ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int geniatech_dvbs_set_voltage(struct dvb_frontend *fe,
				      enum fe_sec_voltage voltage)
{
	struct cx8802_dev *dev = fe->dvb->priv;
	struct cx88_core *core = dev->core;

	if (voltage == SEC_VOLTAGE_OFF) {
		dprintk(1, "LNB Voltage OFF\n");
		cx_write(MO_GP0_IO, 0x0000efff);
	}

	if (core->prev_set_voltage)
		return core->prev_set_voltage(fe, voltage);
	return 0;
}