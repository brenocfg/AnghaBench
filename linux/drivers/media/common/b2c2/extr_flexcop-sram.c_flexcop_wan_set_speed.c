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
struct flexcop_device {int dummy; } ;
typedef  int /*<<< orphan*/  flexcop_wan_speed_t ;

/* Variables and functions */
 int /*<<< orphan*/  flexcop_set_ibi_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wan_ctrl_reg_71c ; 
 int /*<<< orphan*/  wan_speed_sig ; 

void flexcop_wan_set_speed(struct flexcop_device *fc, flexcop_wan_speed_t s)
{
	flexcop_set_ibi_value(wan_ctrl_reg_71c,wan_speed_sig,s);
}