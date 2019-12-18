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
struct dvb_frontend {int dummy; } ;
typedef  enum tda18271_pll { ____Placeholder_tda18271_pll } tda18271_pll ;

/* Variables and functions */
 int __tda18271_charge_pump_source (struct dvb_frontend*,int,int,int) ; 

int tda18271_charge_pump_source(struct dvb_frontend *fe,
				enum tda18271_pll pll, int force)
{
	return __tda18271_charge_pump_source(fe, pll, force, true);
}