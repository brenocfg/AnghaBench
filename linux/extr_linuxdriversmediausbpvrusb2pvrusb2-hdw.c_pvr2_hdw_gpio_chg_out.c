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
typedef  int u32 ;
struct pvr2_hdw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_GPIO_OUT ; 
 int /*<<< orphan*/  PVR2_TRACE_GPIO ; 
 int pvr2_read_register (struct pvr2_hdw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int,...) ; 
 int pvr2_write_register (struct pvr2_hdw*,int /*<<< orphan*/ ,int) ; 

int pvr2_hdw_gpio_chg_out(struct pvr2_hdw *hdw,u32 msk,u32 val)
{
	u32 cval,nval;
	int ret;
	if (~msk) {
		ret = pvr2_read_register(hdw,PVR2_GPIO_OUT,&cval);
		if (ret) return ret;
		nval = (cval & ~msk) | (val & msk);
		pvr2_trace(PVR2_TRACE_GPIO,
			   "GPIO output changing 0x%x:0x%x from 0x%x to 0x%x",
			   msk,val,cval,nval);
	} else {
		nval = val;
		pvr2_trace(PVR2_TRACE_GPIO,
			   "GPIO output changing to 0x%x",nval);
	}
	return pvr2_write_register(hdw,PVR2_GPIO_OUT,nval);
}