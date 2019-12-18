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
struct tda18271_priv {scalar_t__ role; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDA18271_CAL_PLL ; 
 int /*<<< orphan*/  TDA18271_MAIN_PLL ; 
 scalar_t__ TDA18271_SLAVE ; 
 int tda18271_charge_pump_source (struct dvb_frontend*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int charge_pump_source(struct dvb_frontend *fe, int force)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	return tda18271_charge_pump_source(fe,
					   (priv->role == TDA18271_SLAVE) ?
					   TDA18271_CAL_PLL :
					   TDA18271_MAIN_PLL, force);
}