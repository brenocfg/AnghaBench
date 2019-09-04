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
typedef  int u64 ;
struct hv_guest_mapping_flush {int address_space; scalar_t__ flags; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE ; 
 int HV_HYPERCALL_RESULT_MASK ; 
 int hv_do_hypercall (int /*<<< orphan*/ ,struct hv_guest_mapping_flush*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hv_hypercall_pg ; 
 int /*<<< orphan*/  hyperv_pcpu_input_arg ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hyperv_nested_flush_guest_mapping (int,int) ; 
 scalar_t__ unlikely (int) ; 

int hyperv_flush_guest_mapping(u64 as)
{
	struct hv_guest_mapping_flush **flush_pcpu;
	struct hv_guest_mapping_flush *flush;
	u64 status;
	unsigned long flags;
	int ret = -ENOTSUPP;

	if (!hv_hypercall_pg)
		goto fault;

	local_irq_save(flags);

	flush_pcpu = (struct hv_guest_mapping_flush **)
		this_cpu_ptr(hyperv_pcpu_input_arg);

	flush = *flush_pcpu;

	if (unlikely(!flush)) {
		local_irq_restore(flags);
		goto fault;
	}

	flush->address_space = as;
	flush->flags = 0;

	status = hv_do_hypercall(HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE,
				 flush, NULL);
	local_irq_restore(flags);

	if (!(status & HV_HYPERCALL_RESULT_MASK))
		ret = 0;

fault:
	trace_hyperv_nested_flush_guest_mapping(as, ret);
	return ret;
}