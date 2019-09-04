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
struct its_vlpi_map {int dummy; } ;
struct TYPE_2__ {struct its_vlpi_map* map; } ;
struct its_cmd_info {TYPE_1__ member_1; int /*<<< orphan*/  cmd_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_VLPI ; 
 int irq_set_vcpu_affinity (int,struct its_cmd_info*) ; 

int its_get_vlpi(int irq, struct its_vlpi_map *map)
{
	struct its_cmd_info info = {
		.cmd_type = GET_VLPI,
		{
			.map      = map,
		},
	};

	return irq_set_vcpu_affinity(irq, &info);
}