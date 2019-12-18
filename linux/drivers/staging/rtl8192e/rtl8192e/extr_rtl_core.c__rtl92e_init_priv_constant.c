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
struct rt_pwr_save_ctrl {int RegMaxLPSAwakeIntvl; } ;
struct r8192_priv {TYPE_1__* rtllib; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  PowerSaveControl; } ;

/* Variables and functions */
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_init_priv_constant(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	struct rt_pwr_save_ctrl *pPSC = (struct rt_pwr_save_ctrl *)
					&priv->rtllib->PowerSaveControl;

	pPSC->RegMaxLPSAwakeIntvl = 5;
}