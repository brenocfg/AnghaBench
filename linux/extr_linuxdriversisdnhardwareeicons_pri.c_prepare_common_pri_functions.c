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
struct TYPE_5__ {int /*<<< orphan*/  istream_wakeup; int /*<<< orphan*/  ram_in_dw; int /*<<< orphan*/  ram_out_dw; int /*<<< orphan*/  ram_offset; int /*<<< orphan*/  ram_inc; int /*<<< orphan*/  ram_out_buffer; int /*<<< orphan*/  ram_outw; int /*<<< orphan*/  ram_out; int /*<<< orphan*/  ram_look_ahead; int /*<<< orphan*/  ram_in_buffer; int /*<<< orphan*/  ram_inw; int /*<<< orphan*/  ram_in; } ;
struct TYPE_4__ {int /*<<< orphan*/  diva_isr_handler; int /*<<< orphan*/  trapFnc; int /*<<< orphan*/  stop; int /*<<< orphan*/  rstFnc; int /*<<< orphan*/  disIrq; int /*<<< orphan*/  load; struct pc_maint* pcm; int /*<<< orphan*/  clr_irq; int /*<<< orphan*/  tst_irq; int /*<<< orphan*/  dpc; int /*<<< orphan*/  out; TYPE_2__ a; } ;
typedef  TYPE_1__* PISDN_ADAPTER ;
typedef  TYPE_2__ ADAPTER ;

/* Variables and functions */
 scalar_t__ MIPS_MAINT_OFFS ; 
 scalar_t__ MP_SHARED_RAM_OFFSET ; 
 int /*<<< orphan*/  disable_pri_interrupt ; 
 int /*<<< orphan*/  load_pri_hardware ; 
 int /*<<< orphan*/  mem_in ; 
 int /*<<< orphan*/  mem_in_buffer ; 
 int /*<<< orphan*/  mem_in_dw ; 
 int /*<<< orphan*/  mem_inc ; 
 int /*<<< orphan*/  mem_inw ; 
 int /*<<< orphan*/  mem_look_ahead ; 
 int /*<<< orphan*/  mem_out ; 
 int /*<<< orphan*/  mem_out_buffer ; 
 int /*<<< orphan*/  mem_out_dw ; 
 int /*<<< orphan*/  mem_outw ; 
 int /*<<< orphan*/  pr_dpc ; 
 int /*<<< orphan*/  pr_out ; 
 int /*<<< orphan*/  pr_stream ; 
 int /*<<< orphan*/  pri_ISR ; 
 int /*<<< orphan*/  pri_cpu_trapped ; 
 int /*<<< orphan*/  pri_ram_offset ; 
 int /*<<< orphan*/  reset_pri_hardware ; 
 int /*<<< orphan*/  scom_clear_int ; 
 int /*<<< orphan*/  scom_test_int ; 
 int /*<<< orphan*/  stop_pri_hardware ; 

__attribute__((used)) static void prepare_common_pri_functions(PISDN_ADAPTER IoAdapter) {
	ADAPTER *a = &IoAdapter->a;
	a->ram_in           = mem_in;
	a->ram_inw          = mem_inw;
	a->ram_in_buffer    = mem_in_buffer;
	a->ram_look_ahead   = mem_look_ahead;
	a->ram_out          = mem_out;
	a->ram_outw         = mem_outw;
	a->ram_out_buffer   = mem_out_buffer;
	a->ram_inc          = mem_inc;
	a->ram_offset       = pri_ram_offset;
	a->ram_out_dw    = mem_out_dw;
	a->ram_in_dw    = mem_in_dw;
	a->istream_wakeup   = pr_stream;
	IoAdapter->out      = pr_out;
	IoAdapter->dpc      = pr_dpc;
	IoAdapter->tst_irq  = scom_test_int;
	IoAdapter->clr_irq  = scom_clear_int;
	IoAdapter->pcm      = (struct pc_maint *)(MIPS_MAINT_OFFS
						  - MP_SHARED_RAM_OFFSET);
	IoAdapter->load     = load_pri_hardware;
	IoAdapter->disIrq   = disable_pri_interrupt;
	IoAdapter->rstFnc   = reset_pri_hardware;
	IoAdapter->stop     = stop_pri_hardware;
	IoAdapter->trapFnc  = pri_cpu_trapped;
	IoAdapter->diva_isr_handler = pri_ISR;
}