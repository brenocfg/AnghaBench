#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vmcb_control_area {int /*<<< orphan*/  virt_ext; int /*<<< orphan*/  nested_cr3; int /*<<< orphan*/  event_inj_err; int /*<<< orphan*/  event_inj; int /*<<< orphan*/  nested_ctl; int /*<<< orphan*/  exit_int_info_err; int /*<<< orphan*/  exit_int_info; int /*<<< orphan*/  exit_info_2; int /*<<< orphan*/  exit_info_1; int /*<<< orphan*/  exit_code_hi; int /*<<< orphan*/  exit_code; int /*<<< orphan*/  int_state; int /*<<< orphan*/  int_vector; int /*<<< orphan*/  int_ctl; int /*<<< orphan*/  tlb_ctl; int /*<<< orphan*/  asid; int /*<<< orphan*/  tsc_offset; int /*<<< orphan*/  msrpm_base_pa; int /*<<< orphan*/  iopm_base_pa; int /*<<< orphan*/  intercept; int /*<<< orphan*/  intercept_exceptions; int /*<<< orphan*/  intercept_dr; int /*<<< orphan*/  intercept_cr; } ;
struct vmcb {struct vmcb_control_area control; } ;

/* Variables and functions */

__attribute__((used)) static inline void copy_vmcb_control_area(struct vmcb *dst_vmcb, struct vmcb *from_vmcb)
{
	struct vmcb_control_area *dst  = &dst_vmcb->control;
	struct vmcb_control_area *from = &from_vmcb->control;

	dst->intercept_cr         = from->intercept_cr;
	dst->intercept_dr         = from->intercept_dr;
	dst->intercept_exceptions = from->intercept_exceptions;
	dst->intercept            = from->intercept;
	dst->iopm_base_pa         = from->iopm_base_pa;
	dst->msrpm_base_pa        = from->msrpm_base_pa;
	dst->tsc_offset           = from->tsc_offset;
	dst->asid                 = from->asid;
	dst->tlb_ctl              = from->tlb_ctl;
	dst->int_ctl              = from->int_ctl;
	dst->int_vector           = from->int_vector;
	dst->int_state            = from->int_state;
	dst->exit_code            = from->exit_code;
	dst->exit_code_hi         = from->exit_code_hi;
	dst->exit_info_1          = from->exit_info_1;
	dst->exit_info_2          = from->exit_info_2;
	dst->exit_int_info        = from->exit_int_info;
	dst->exit_int_info_err    = from->exit_int_info_err;
	dst->nested_ctl           = from->nested_ctl;
	dst->event_inj            = from->event_inj;
	dst->event_inj_err        = from->event_inj_err;
	dst->nested_cr3           = from->nested_cr3;
	dst->virt_ext              = from->virt_ext;
}