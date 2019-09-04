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
typedef  int u32 ;
struct TYPE_2__ {int mask; } ;
struct sim_dev_reg {TYPE_1__ sim_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_read (struct sim_dev_reg*,int*) ; 

__attribute__((used)) static void ehci_reg_read(struct sim_dev_reg *reg, u32 *value)
{
	reg_read(reg, value);
	if (*value != reg->sim_reg.mask)
		*value |= 0x100;
}