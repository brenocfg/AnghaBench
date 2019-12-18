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
struct xmit_frame {int dummy; } ;
struct TYPE_2__ {int (* hal_xmitframe_enqueue ) (struct adapter*,struct xmit_frame*) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;
typedef  int s32 ;

/* Variables and functions */
 int stub1 (struct adapter*,struct xmit_frame*) ; 

s32	rtw_hal_xmitframe_enqueue(struct adapter *padapter, struct xmit_frame *pxmitframe)
{
	if (padapter->HalFunc.hal_xmitframe_enqueue)
		return padapter->HalFunc.hal_xmitframe_enqueue(padapter, pxmitframe);

	return false;
}