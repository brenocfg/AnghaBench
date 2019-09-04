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
struct TYPE_3__ {int pnode_shift; } ;
struct TYPE_4__ {TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ uvh_apicid ; 
 int /*<<< orphan*/  x2apic_extra_bits ; 

__attribute__((used)) static void set_x2apic_extra_bits(int pnode)
{
	__this_cpu_write(x2apic_extra_bits, pnode << uvh_apicid.s.pnode_shift);
}