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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  config; } ;
struct its_cmd_info {TYPE_1__ member_1; int /*<<< orphan*/  cmd_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROP_UPDATE_AND_INV_VLPI ; 
 int /*<<< orphan*/  PROP_UPDATE_VLPI ; 
 int irq_set_vcpu_affinity (int,struct its_cmd_info*) ; 

int its_prop_update_vlpi(int irq, u8 config, bool inv)
{
	struct its_cmd_info info = {
		.cmd_type = inv ? PROP_UPDATE_AND_INV_VLPI : PROP_UPDATE_VLPI,
		{
			.config   = config,
		},
	};

	return irq_set_vcpu_affinity(irq, &info);
}