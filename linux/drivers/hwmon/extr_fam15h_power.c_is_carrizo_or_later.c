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
struct TYPE_2__ {int x86; int x86_model; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static bool is_carrizo_or_later(void)
{
	return boot_cpu_data.x86 == 0x15 && boot_cpu_data.x86_model >= 0x60;
}