#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dvb_frontend {int /*<<< orphan*/ * sec_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_VOLTAGE_OFF ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lnbp21_set_voltage (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lnbp21_release(struct dvb_frontend *fe)
{
	/* LNBP power off */
	lnbp21_set_voltage(fe, SEC_VOLTAGE_OFF);

	/* free data */
	kfree(fe->sec_priv);
	fe->sec_priv = NULL;
}