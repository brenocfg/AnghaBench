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
typedef  scalar_t__ u32 ;
struct host1x {scalar_t__ hv_regs; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 

u32 host1x_hypervisor_readl(struct host1x *host1x, u32 r)
{
	return readl(host1x->hv_regs + r);
}