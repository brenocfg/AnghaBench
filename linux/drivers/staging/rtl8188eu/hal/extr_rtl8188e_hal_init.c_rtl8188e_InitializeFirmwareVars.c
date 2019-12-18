#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bFwCurrentInPSMode; } ;
struct adapter {TYPE_2__* HalData; TYPE_1__ pwrctrlpriv; } ;
struct TYPE_4__ {scalar_t__ LastHMEBoxNum; } ;

/* Variables and functions */

void rtl8188e_InitializeFirmwareVars(struct adapter *padapter)
{
	/*  Init Fw LPS related. */
	padapter->pwrctrlpriv.bFwCurrentInPSMode = false;

	/*  Init H2C counter. by tynli. 2009.12.09. */
	padapter->HalData->LastHMEBoxNum = 0;
}