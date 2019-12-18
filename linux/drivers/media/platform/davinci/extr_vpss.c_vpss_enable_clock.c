#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum vpss_clock_sel { ____Placeholder_vpss_clock_sel } vpss_clock_sel ;
struct TYPE_3__ {int (* enable_clock ) (int,int) ;} ;
struct TYPE_4__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__ oper_cfg ; 
 int stub1 (int,int) ; 

int vpss_enable_clock(enum vpss_clock_sel clock_sel, int en)
{
	if (!oper_cfg.hw_ops.enable_clock)
		return -EINVAL;

	return oper_cfg.hw_ops.enable_clock(clock_sel, en);
}