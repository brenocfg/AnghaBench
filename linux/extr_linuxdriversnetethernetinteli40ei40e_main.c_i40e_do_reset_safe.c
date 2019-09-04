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
typedef  int /*<<< orphan*/  u32 ;
struct i40e_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_do_reset (struct i40e_pf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void i40e_do_reset_safe(struct i40e_pf *pf, u32 reset_flags)
{
	rtnl_lock();
	i40e_do_reset(pf, reset_flags, true);
	rtnl_unlock();
}