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
struct TYPE_4__ {scalar_t__ x86_max_cores; } ;
struct TYPE_3__ {scalar_t__ num_boxes; } ;

/* Variables and functions */
 TYPE_2__ boot_cpu_data ; 
 int /*<<< orphan*/  ivbep_msr_uncores ; 
 TYPE_1__ ivbep_uncore_cbox ; 
 int /*<<< orphan*/  uncore_msr_uncores ; 

void ivbep_uncore_cpu_init(void)
{
	if (ivbep_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		ivbep_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
	uncore_msr_uncores = ivbep_msr_uncores;
}