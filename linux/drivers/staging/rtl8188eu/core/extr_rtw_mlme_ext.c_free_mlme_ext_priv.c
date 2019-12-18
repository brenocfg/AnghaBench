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
struct mlme_ext_priv {int /*<<< orphan*/  link_timer; int /*<<< orphan*/  survey_timer; struct adapter* padapter; } ;
struct adapter {scalar_t__ bDriverStopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

void free_mlme_ext_priv(struct mlme_ext_priv *pmlmeext)
{
	struct adapter *padapter = pmlmeext->padapter;

	if (!padapter)
		return;

	if (padapter->bDriverStopped) {
		del_timer_sync(&pmlmeext->survey_timer);
		del_timer_sync(&pmlmeext->link_timer);
	}
}