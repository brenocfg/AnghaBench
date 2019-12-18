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
struct TYPE_2__ {int /*<<< orphan*/  sitesurvey_ctrl_timer; } ;
struct mlme_priv {int /*<<< orphan*/  wdg_timer; int /*<<< orphan*/  dhcp_timer; int /*<<< orphan*/  scan_to_timer; TYPE_1__ sitesurveyctrl; int /*<<< orphan*/  assoc_timer; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _scan_timeout_handler ; 
 int /*<<< orphan*/  dhcp_timeout_handler ; 
 int /*<<< orphan*/  join_timeout_handler ; 
 int /*<<< orphan*/  sitesurvey_ctrl_handler ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdg_timeout_handler ; 

void r8712_init_mlme_timer(struct _adapter *adapter)
{
	struct	mlme_priv *mlmepriv = &adapter->mlmepriv;

	timer_setup(&mlmepriv->assoc_timer, join_timeout_handler, 0);
	timer_setup(&mlmepriv->sitesurveyctrl.sitesurvey_ctrl_timer,
		    sitesurvey_ctrl_handler, 0);
	timer_setup(&mlmepriv->scan_to_timer, _scan_timeout_handler, 0);
	timer_setup(&mlmepriv->dhcp_timer, dhcp_timeout_handler, 0);
	timer_setup(&mlmepriv->wdg_timer, wdg_timeout_handler, 0);
}