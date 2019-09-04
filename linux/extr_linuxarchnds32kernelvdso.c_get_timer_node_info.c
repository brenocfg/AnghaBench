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
struct TYPE_4__ {int /*<<< orphan*/  cycle_count_down; int /*<<< orphan*/  cycle_count_reg_offset; int /*<<< orphan*/  mapping_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  cycle_count_down; int /*<<< orphan*/  cycle_count_offset; } ;

/* Variables and functions */
 TYPE_2__ timer_info ; 
 int /*<<< orphan*/  timer_mapping_base ; 
 TYPE_1__* vdso_data ; 

__attribute__((used)) static void get_timer_node_info(void)
{
	timer_mapping_base = timer_info.mapping_base;
	vdso_data->cycle_count_offset =
		timer_info.cycle_count_reg_offset;
	vdso_data->cycle_count_down =
		timer_info.cycle_count_down;
}