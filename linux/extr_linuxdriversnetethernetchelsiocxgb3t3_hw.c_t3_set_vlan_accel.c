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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_OUT_CONFIG ; 
 unsigned int S_VLANEXTRACTIONENABLE ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

void t3_set_vlan_accel(struct adapter *adapter, unsigned int ports, int on)
{
	t3_set_reg_field(adapter, A_TP_OUT_CONFIG,
			 ports << S_VLANEXTRACTIONENABLE,
			 on ? (ports << S_VLANEXTRACTIONENABLE) : 0);
}