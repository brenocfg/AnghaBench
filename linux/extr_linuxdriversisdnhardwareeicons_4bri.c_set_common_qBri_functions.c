#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pc_maint {int dummy; } ;
struct TYPE_5__ {void* io; int /*<<< orphan*/  ram_inc; int /*<<< orphan*/  ram_out_buffer; int /*<<< orphan*/  ram_outw; int /*<<< orphan*/  ram_out; int /*<<< orphan*/  ram_look_ahead; int /*<<< orphan*/  ram_in_buffer; int /*<<< orphan*/  ram_inw; int /*<<< orphan*/  ram_in; } ;
struct TYPE_4__ {TYPE_2__ a; int /*<<< orphan*/  diva_isr_handler; int /*<<< orphan*/  trapFnc; int /*<<< orphan*/  stop; int /*<<< orphan*/  rstFnc; int /*<<< orphan*/  disIrq; int /*<<< orphan*/  load; struct pc_maint* pcm; int /*<<< orphan*/  clr_irq; int /*<<< orphan*/  tst_irq; int /*<<< orphan*/  dpc; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__* PISDN_ADAPTER ;
typedef  TYPE_2__ ADAPTER ;

/* Variables and functions */
 scalar_t__ MIPS_MAINT_OFFS ; 
 int /*<<< orphan*/  disable_qBri_interrupt ; 
 int /*<<< orphan*/  load_qBri_hardware ; 
 int /*<<< orphan*/  mem_in ; 
 int /*<<< orphan*/  mem_in_buffer ; 
 int /*<<< orphan*/  mem_inc ; 
 int /*<<< orphan*/  mem_inw ; 
 int /*<<< orphan*/  mem_look_ahead ; 
 int /*<<< orphan*/  mem_out ; 
 int /*<<< orphan*/  mem_out_buffer ; 
 int /*<<< orphan*/  mem_outw ; 
 int /*<<< orphan*/  pr_dpc ; 
 int /*<<< orphan*/  pr_out ; 
 int /*<<< orphan*/  qBri_ISR ; 
 int /*<<< orphan*/  qBri_cpu_trapped ; 
 int /*<<< orphan*/  reset_qBri_hardware ; 
 int /*<<< orphan*/  scom_clear_int ; 
 int /*<<< orphan*/  scom_test_int ; 
 int /*<<< orphan*/  stop_qBri_hardware ; 

__attribute__((used)) static void set_common_qBri_functions(PISDN_ADAPTER IoAdapter) {
	ADAPTER *a;

	a = &IoAdapter->a;

	a->ram_in           = mem_in;
	a->ram_inw          = mem_inw;
	a->ram_in_buffer    = mem_in_buffer;
	a->ram_look_ahead   = mem_look_ahead;
	a->ram_out          = mem_out;
	a->ram_outw         = mem_outw;
	a->ram_out_buffer   = mem_out_buffer;
	a->ram_inc          = mem_inc;

	IoAdapter->out = pr_out;
	IoAdapter->dpc = pr_dpc;
	IoAdapter->tst_irq = scom_test_int;
	IoAdapter->clr_irq  = scom_clear_int;
	IoAdapter->pcm  = (struct pc_maint *)MIPS_MAINT_OFFS;

	IoAdapter->load = load_qBri_hardware;

	IoAdapter->disIrq = disable_qBri_interrupt;
	IoAdapter->rstFnc = reset_qBri_hardware;
	IoAdapter->stop = stop_qBri_hardware;
	IoAdapter->trapFnc = qBri_cpu_trapped;

	IoAdapter->diva_isr_handler = qBri_ISR;

	IoAdapter->a.io = (void *)IoAdapter;
}