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
struct TYPE_2__ {int asoc_sta_count; } ;
struct adapter {int /*<<< orphan*/  mlmepriv; TYPE_1__ stapriv; } ;
typedef  int sint ;

/* Variables and functions */
 int WIFI_ADHOC_MASTER_STATE ; 
 int WIFI_ADHOC_STATE ; 
 int WIFI_AP_STATE ; 
 int _FW_LINKED ; 
 int check_fwstate (int /*<<< orphan*/ *,int) ; 

sint rtw_linked_check(struct adapter *padapter)
{
	if ((check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == true) ||
			(check_fwstate(&padapter->mlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE) == true)) {
		if (padapter->stapriv.asoc_sta_count > 2)
			return true;
	} else {	/* Station mode */
		if (check_fwstate(&padapter->mlmepriv, _FW_LINKED) == true)
			return true;
	}
	return false;
}