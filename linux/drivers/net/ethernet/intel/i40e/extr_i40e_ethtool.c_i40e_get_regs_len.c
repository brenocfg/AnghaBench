#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ elements; } ;

/* Variables and functions */
 TYPE_1__* i40e_reg_list ; 

__attribute__((used)) static int i40e_get_regs_len(struct net_device *netdev)
{
	int reg_count = 0;
	int i;

	for (i = 0; i40e_reg_list[i].offset != 0; i++)
		reg_count += i40e_reg_list[i].elements;

	return reg_count * sizeof(u32);
}