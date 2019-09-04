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
 int /*<<< orphan*/  A_TP_IN_CONFIG ; 
 int /*<<< orphan*/  F_NICMODE ; 
 int /*<<< orphan*/  V_NICMODE (int) ; 
 scalar_t__ is_offload (struct adapter*) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t3_tp_set_offload_mode(struct adapter *adap, int enable)
{
	if (is_offload(adap) || !enable)
		t3_set_reg_field(adap, A_TP_IN_CONFIG, F_NICMODE,
				 V_NICMODE(!enable));
}