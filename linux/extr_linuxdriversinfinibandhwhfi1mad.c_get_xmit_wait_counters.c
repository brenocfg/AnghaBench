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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct hfi1_pportdata {scalar_t__* vl_xmit_flit_cnt; int /*<<< orphan*/  prev_link_width; scalar_t__* port_vl_xmit_wait_last; } ;

/* Variables and functions */
 int CNTR_INVALID_VL ; 
 int /*<<< orphan*/  C_TX_WAIT ; 
 int /*<<< orphan*/  C_TX_WAIT_VL ; 
 int C_VL_COUNT ; 
 scalar_t__ convert_xmit_counter (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_port_cntr (struct hfi1_pportdata*,int /*<<< orphan*/ ,int) ; 

u64 get_xmit_wait_counters(struct hfi1_pportdata *ppd,
			   u16 link_width, u16 link_speed, int vl)
{
	u64 port_vl_xmit_wait_curr;
	u64 delta_vl_xmit_wait;
	u64 xmit_wait_val;

	if (vl > C_VL_COUNT)
		return  0;
	if (vl < C_VL_COUNT)
		port_vl_xmit_wait_curr =
			read_port_cntr(ppd, C_TX_WAIT_VL, vl);
	else
		port_vl_xmit_wait_curr =
			read_port_cntr(ppd, C_TX_WAIT, CNTR_INVALID_VL);

	xmit_wait_val =
		port_vl_xmit_wait_curr -
		ppd->port_vl_xmit_wait_last[vl];
	delta_vl_xmit_wait =
		convert_xmit_counter(xmit_wait_val,
				     ppd->prev_link_width,
				     link_speed);

	ppd->vl_xmit_flit_cnt[vl] += delta_vl_xmit_wait;
	ppd->port_vl_xmit_wait_last[vl] = port_vl_xmit_wait_curr;
	ppd->prev_link_width = link_width;

	return ppd->vl_xmit_flit_cnt[vl];
}