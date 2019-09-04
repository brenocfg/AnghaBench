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

/* Variables and functions */
#define  H_BULK_REMOVE 137 
#define  H_CEDE 136 
#define  H_ENTER 135 
#define  H_LOGICAL_CI_LOAD 134 
#define  H_LOGICAL_CI_STORE 133 
#define  H_PROTECT 132 
#define  H_PUT_TCE 131 
#define  H_PUT_TCE_INDIRECT 130 
#define  H_REMOVE 129 
#define  H_STUFF_TCE 128 

int kvmppc_hcall_impl_pr(unsigned long cmd)
{
	switch (cmd) {
	case H_ENTER:
	case H_REMOVE:
	case H_PROTECT:
	case H_BULK_REMOVE:
	case H_PUT_TCE:
	case H_PUT_TCE_INDIRECT:
	case H_STUFF_TCE:
	case H_CEDE:
	case H_LOGICAL_CI_LOAD:
	case H_LOGICAL_CI_STORE:
#ifdef CONFIG_KVM_XICS
	case H_XIRR:
	case H_CPPR:
	case H_EOI:
	case H_IPI:
	case H_IPOLL:
	case H_XIRR_X:
#endif
		return 1;
	}
	return 0;
}