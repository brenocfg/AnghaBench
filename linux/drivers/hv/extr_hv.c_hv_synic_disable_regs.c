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
union hv_synic_sint {int masked; int /*<<< orphan*/  as_uint64; } ;
union hv_synic_simp {int /*<<< orphan*/  as_uint64; scalar_t__ base_simp_gpa; scalar_t__ simp_enabled; } ;
union hv_synic_siefp {int /*<<< orphan*/  as_uint64; scalar_t__ base_siefp_gpa; scalar_t__ siefp_enabled; } ;
union hv_synic_scontrol {int /*<<< orphan*/  as_uint64; scalar_t__ enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMBUS_MESSAGE_SINT ; 
 int /*<<< orphan*/  hv_get_siefp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_get_simp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_get_synic_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_get_synint_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_set_siefp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_set_simp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_set_synic_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_set_synint_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hv_synic_disable_regs(unsigned int cpu)
{
	union hv_synic_sint shared_sint;
	union hv_synic_simp simp;
	union hv_synic_siefp siefp;
	union hv_synic_scontrol sctrl;

	hv_get_synint_state(VMBUS_MESSAGE_SINT, shared_sint.as_uint64);

	shared_sint.masked = 1;

	/* Need to correctly cleanup in the case of SMP!!! */
	/* Disable the interrupt */
	hv_set_synint_state(VMBUS_MESSAGE_SINT, shared_sint.as_uint64);

	hv_get_simp(simp.as_uint64);
	simp.simp_enabled = 0;
	simp.base_simp_gpa = 0;

	hv_set_simp(simp.as_uint64);

	hv_get_siefp(siefp.as_uint64);
	siefp.siefp_enabled = 0;
	siefp.base_siefp_gpa = 0;

	hv_set_siefp(siefp.as_uint64);

	/* Disable the global synic bit */
	hv_get_synic_state(sctrl.as_uint64);
	sctrl.enable = 0;
	hv_set_synic_state(sctrl.as_uint64);
}