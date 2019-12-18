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
typedef  int /*<<< orphan*/  u8 ;
struct rtllib_device {scalar_t__ ps; scalar_t__ state; scalar_t__ iw_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* sta_wake_up ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ RTLLIB_LINKED ; 
 scalar_t__ RTLLIB_PS_DISABLED ; 
 int /*<<< orphan*/  rtllib_MgntDisconnectAP (struct rtllib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtllib_MgntDisconnectIBSS (struct rtllib_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

bool rtllib_MgntDisconnect(struct rtllib_device *rtllib, u8 asRsn)
{
	if (rtllib->ps != RTLLIB_PS_DISABLED)
		rtllib->sta_wake_up(rtllib->dev);

	if (rtllib->state == RTLLIB_LINKED) {
		if (rtllib->iw_mode == IW_MODE_ADHOC)
			rtllib_MgntDisconnectIBSS(rtllib);
		if (rtllib->iw_mode == IW_MODE_INFRA)
			rtllib_MgntDisconnectAP(rtllib, asRsn);

	}

	return true;
}