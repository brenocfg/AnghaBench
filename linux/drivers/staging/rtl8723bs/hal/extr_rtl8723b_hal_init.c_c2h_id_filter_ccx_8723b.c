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
struct c2h_evt_hdr_88xx {scalar_t__ id; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ C2H_CCX_TX_RPT ; 

s32 c2h_id_filter_ccx_8723b(u8 *buf)
{
	struct c2h_evt_hdr_88xx *c2h_evt = (struct c2h_evt_hdr_88xx *)buf;
	s32 ret = false;
	if (c2h_evt->id == C2H_CCX_TX_RPT)
		ret = true;

	return ret;
}