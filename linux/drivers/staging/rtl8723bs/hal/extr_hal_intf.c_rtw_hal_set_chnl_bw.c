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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_chnl_bw_handler ) (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;
typedef  enum CHANNEL_WIDTH { ____Placeholder_CHANNEL_WIDTH } CHANNEL_WIDTH ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw_hal_set_chnl_bw(struct adapter *padapter, u8 channel,
			 enum CHANNEL_WIDTH Bandwidth, u8 Offset40, u8 Offset80)
{
	if (padapter->HalFunc.set_chnl_bw_handler)
		padapter->HalFunc.set_chnl_bw_handler(padapter, channel,
						      Bandwidth, Offset40,
						      Offset80);
}