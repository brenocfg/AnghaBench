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
struct mlme_ext_priv {int /*<<< orphan*/  sa_query_timer; int /*<<< orphan*/  link_timer; int /*<<< orphan*/  survey_timer; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  link_timer_hdl ; 
 int /*<<< orphan*/  sa_query_timer_hdl ; 
 int /*<<< orphan*/  survey_timer_hdl ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_mlme_ext_timer(struct adapter *padapter)
{
	struct	mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	timer_setup(&pmlmeext->survey_timer, survey_timer_hdl, 0);
	timer_setup(&pmlmeext->link_timer, link_timer_hdl, 0);
	timer_setup(&pmlmeext->sa_query_timer, sa_query_timer_hdl, 0);
}