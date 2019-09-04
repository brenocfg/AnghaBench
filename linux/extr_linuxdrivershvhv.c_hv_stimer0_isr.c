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
struct hv_per_cpu_context {TYPE_1__* clk_evt; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpu_context; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  add_interrupt_randomness (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ hv_context ; 
 int /*<<< orphan*/  stimer0_vector ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 struct hv_per_cpu_context* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hv_stimer0_isr(void)
{
	struct hv_per_cpu_context *hv_cpu;

	hv_cpu = this_cpu_ptr(hv_context.cpu_context);
	hv_cpu->clk_evt->event_handler(hv_cpu->clk_evt);
	add_interrupt_randomness(stimer0_vector, 0);
}