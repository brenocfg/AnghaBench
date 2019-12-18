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
typedef  int /*<<< orphan*/  u16 ;
struct hfa384x {int dummy; } ;
typedef  int /*<<< orphan*/  ctlx_usercb_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOASYNC ; 
 int /*<<< orphan*/  hfa384x_cb_status ; 
 int hfa384x_dowrid (struct hfa384x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
hfa384x_drvr_setconfig_async(struct hfa384x *hw,
			     u16 rid,
			     void *buf,
			     u16 len, ctlx_usercb_t usercb, void *usercb_data)
{
	return hfa384x_dowrid(hw, DOASYNC, rid, buf, len, hfa384x_cb_status,
			      usercb, usercb_data);
}