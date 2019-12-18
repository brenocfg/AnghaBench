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
struct r8192_priv {scalar_t__ bHwRfOffAction; TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
typedef  enum rt_rf_power_state { ____Placeholder_rt_rf_power_state } rt_rf_power_state ;
struct TYPE_2__ {int eRFPowerState; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_PS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 int _rtl92e_set_rf_power_state (struct net_device*,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

bool rtl92e_set_rf_power_state(struct net_device *dev,
			       enum rt_rf_power_state eRFPowerState)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	bool bResult = false;

	RT_TRACE(COMP_PS,
		 "---------> rtl92e_set_rf_power_state(): eRFPowerState(%d)\n",
		 eRFPowerState);
	if (eRFPowerState == priv->rtllib->eRFPowerState &&
	    priv->bHwRfOffAction == 0) {
		RT_TRACE(COMP_PS,
			 "<--------- rtl92e_set_rf_power_state(): discard the request for eRFPowerState(%d) is the same.\n",
			 eRFPowerState);
		return bResult;
	}

	bResult = _rtl92e_set_rf_power_state(dev, eRFPowerState);

	RT_TRACE(COMP_PS,
		 "<--------- rtl92e_set_rf_power_state(): bResult(%d)\n",
		 bResult);

	return bResult;
}