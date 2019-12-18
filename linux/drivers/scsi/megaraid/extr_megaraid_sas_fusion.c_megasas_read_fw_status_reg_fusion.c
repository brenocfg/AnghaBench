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
struct megasas_instance {TYPE_1__* reg_set; } ;
struct TYPE_2__ {int /*<<< orphan*/  outbound_scratch_pad_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  megasas_readl (struct megasas_instance*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
megasas_read_fw_status_reg_fusion(struct megasas_instance *instance)
{
	return megasas_readl(instance, &instance->reg_set->outbound_scratch_pad_0);
}