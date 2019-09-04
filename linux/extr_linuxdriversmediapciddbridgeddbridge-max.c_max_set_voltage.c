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
struct dvb_frontend {struct ddb_input* sec_priv; } ;
struct ddb_port {size_t lnr; struct ddb_dvb* dvb; struct ddb* dev; } ;
struct ddb_input {int nr; struct ddb_port* port; } ;
struct ddb_dvb {int voltage; size_t input; int /*<<< orphan*/  tone; } ;
struct ddb {TYPE_2__* link; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_3__ {int voltages; int fmode; unsigned long long* voltage; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ lnb; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_TONE_ON ; 
 int SEC_VOLTAGE_13 ; 
 int SEC_VOLTAGE_18 ; 
 int SEC_VOLTAGE_OFF ; 
 int lnb_set_voltage (struct ddb*,size_t,int,int) ; 
 int max_set_input_unlocked (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  old_quattro ; 

__attribute__((used)) static int max_set_voltage(struct dvb_frontend *fe, enum fe_sec_voltage voltage)
{
	struct ddb_input *input = fe->sec_priv;
	struct ddb_port *port = input->port;
	struct ddb *dev = port->dev;
	struct ddb_dvb *dvb = &port->dvb[input->nr & 1];
	int tuner = 0;
	u32 nv, ov = dev->link[port->lnr].lnb.voltages;
	int res = 0;
	u32 fmode = dev->link[port->lnr].lnb.fmode;

	mutex_lock(&dev->link[port->lnr].lnb.lock);
	dvb->voltage = voltage;

	switch (fmode) {
	case 3:
	default:
	case 0:
		if (fmode == 3)
			max_set_input_unlocked(fe, 0);
		if (voltage == SEC_VOLTAGE_OFF)
			dev->link[port->lnr].lnb.voltage[dvb->input] &=
				~(1ULL << input->nr);
		else
			dev->link[port->lnr].lnb.voltage[dvb->input] |=
				(1ULL << input->nr);

		res = lnb_set_voltage(dev, port->lnr, dvb->input, voltage);
		break;
	case 1:
	case 2:
		if (voltage == SEC_VOLTAGE_OFF)
			dev->link[port->lnr].lnb.voltages &=
				~(1ULL << input->nr);
		else
			dev->link[port->lnr].lnb.voltages |=
				(1ULL << input->nr);

		nv = dev->link[port->lnr].lnb.voltages;

		if (old_quattro) {
			if (dvb->tone == SEC_TONE_ON)
				tuner |= 2;
			if (dvb->voltage == SEC_VOLTAGE_18)
				tuner |= 1;
		} else {
			if (dvb->tone == SEC_TONE_ON)
				tuner |= 1;
			if (dvb->voltage == SEC_VOLTAGE_18)
				tuner |= 2;
		}
		res = max_set_input_unlocked(fe, tuner);

		if (nv != ov) {
			if (nv) {
				lnb_set_voltage(
					dev, port->lnr,
					0, SEC_VOLTAGE_13);
				if (fmode == 1) {
					lnb_set_voltage(
						dev, port->lnr,
						0, SEC_VOLTAGE_13);
					if (old_quattro) {
						lnb_set_voltage(
							dev, port->lnr,
							1, SEC_VOLTAGE_18);
						lnb_set_voltage(
							dev, port->lnr,
							2, SEC_VOLTAGE_13);
					} else {
						lnb_set_voltage(
							dev, port->lnr,
							1, SEC_VOLTAGE_13);
						lnb_set_voltage(
							dev, port->lnr,
							2, SEC_VOLTAGE_18);
					}
					lnb_set_voltage(
						dev, port->lnr,
						3, SEC_VOLTAGE_18);
				}
			} else {
				lnb_set_voltage(
					dev, port->lnr,
					0, SEC_VOLTAGE_OFF);
				if (fmode == 1) {
					lnb_set_voltage(
						dev, port->lnr,
						1, SEC_VOLTAGE_OFF);
					lnb_set_voltage(
						dev, port->lnr,
						2, SEC_VOLTAGE_OFF);
					lnb_set_voltage(
						dev, port->lnr,
						3, SEC_VOLTAGE_OFF);
				}
			}
		}
		break;
	}
	mutex_unlock(&dev->link[port->lnr].lnb.lock);
	return res;
}