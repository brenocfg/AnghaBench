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
typedef  union recv_frame {int dummy; } recv_frame ;
struct TYPE_2__ {scalar_t__ state; } ;
struct mlme_ext_priv {TYPE_1__ sitesurvey_res; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 scalar_t__ SCAN_PROCESS ; 
 unsigned int _SUCCESS ; 
 int /*<<< orphan*/  report_survey_event (struct adapter*,union recv_frame*) ; 

unsigned int OnProbeRsp(struct adapter *padapter, union recv_frame *precv_frame)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;

	if (pmlmeext->sitesurvey_res.state == SCAN_PROCESS) {
		report_survey_event(padapter, precv_frame);
		return _SUCCESS;
	}

	return _SUCCESS;

}