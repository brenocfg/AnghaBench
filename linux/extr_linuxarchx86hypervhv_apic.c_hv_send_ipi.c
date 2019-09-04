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
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI ) (int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __send_ipi_one (int,int) ; 
 TYPE_1__ orig_apic ; 
 int /*<<< orphan*/  stub1 (int,int) ; 

__attribute__((used)) static void hv_send_ipi(int cpu, int vector)
{
	if (!__send_ipi_one(cpu, vector))
		orig_apic.send_IPI(cpu, vector);
}