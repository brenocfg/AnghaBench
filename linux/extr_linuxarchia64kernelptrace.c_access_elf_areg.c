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
struct unw_frame_info {int dummy; } ;
struct task_struct {int dummy; } ;
struct pt_regs {unsigned long ar_rsc; unsigned long ar_bspstore; unsigned long ar_rnat; unsigned long ar_ccv; unsigned long ar_unat; unsigned long ar_fpsr; unsigned long ar_pfs; unsigned long ar_csd; unsigned long ar_ssd; unsigned long cr_iip; unsigned long cr_ifs; unsigned long cr_ipsr; unsigned long pr; int /*<<< orphan*/  loadrs; } ;

/* Variables and functions */
#define  ELF_AR_BSPSTORE_OFFSET 142 
#define  ELF_AR_BSP_OFFSET 141 
#define  ELF_AR_CCV_OFFSET 140 
#define  ELF_AR_CSD_OFFSET 139 
#define  ELF_AR_EC_OFFSET 138 
#define  ELF_AR_FPSR_OFFSET 137 
#define  ELF_AR_LC_OFFSET 136 
#define  ELF_AR_PFS_OFFSET 135 
#define  ELF_AR_RNAT_OFFSET 134 
#define  ELF_AR_RSC_OFFSET 133 
#define  ELF_AR_SSD_OFFSET 132 
#define  ELF_AR_UNAT_OFFSET 131 
#define  ELF_CFM_OFFSET 130 
#define  ELF_CR_IIP_OFFSET 129 
#define  ELF_CR_IPSR_OFFSET 128 
 unsigned long ELF_NAT_OFFSET ; 
 unsigned long ELF_PR_OFFSET ; 
 unsigned long IA64_PSR_RI ; 
 unsigned long IPSR_MASK ; 
 unsigned long PFM_MASK ; 
 int /*<<< orphan*/  UNW_AR_EC ; 
 int /*<<< orphan*/  UNW_AR_LC ; 
 int access_nat_bits (struct task_struct*,struct pt_regs*,struct unw_frame_info*,unsigned long*,int) ; 
 int /*<<< orphan*/  convert_to_non_syscall (struct task_struct*,struct pt_regs*,unsigned long) ; 
 unsigned long ia64_get_user_rbs_end (struct task_struct*,struct pt_regs*,unsigned long*) ; 
 int /*<<< orphan*/  in_syscall (struct pt_regs*) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 int unw_access_ar (struct unw_frame_info*,int /*<<< orphan*/ ,unsigned long*,int) ; 

__attribute__((used)) static int
access_elf_areg(struct task_struct *target, struct unw_frame_info *info,
		unsigned long addr, unsigned long *data, int write_access)
{
	struct pt_regs *pt;
	unsigned long cfm, urbs_end;
	unsigned long *ptr = NULL;

	pt = task_pt_regs(target);
	if (addr >= ELF_AR_RSC_OFFSET && addr <= ELF_AR_SSD_OFFSET) {
		switch (addr) {
		case ELF_AR_RSC_OFFSET:
			/* force PL3 */
			if (write_access)
				pt->ar_rsc = *data | (3 << 2);
			else
				*data = pt->ar_rsc;
			return 0;
		case ELF_AR_BSP_OFFSET:
			/*
			 * By convention, we use PT_AR_BSP to refer to
			 * the end of the user-level backing store.
			 * Use ia64_rse_skip_regs(PT_AR_BSP, -CFM.sof)
			 * to get the real value of ar.bsp at the time
			 * the kernel was entered.
			 *
			 * Furthermore, when changing the contents of
			 * PT_AR_BSP (or PT_CFM) while the task is
			 * blocked in a system call, convert the state
			 * so that the non-system-call exit
			 * path is used.  This ensures that the proper
			 * state will be picked up when resuming
			 * execution.  However, it *also* means that
			 * once we write PT_AR_BSP/PT_CFM, it won't be
			 * possible to modify the syscall arguments of
			 * the pending system call any longer.  This
			 * shouldn't be an issue because modifying
			 * PT_AR_BSP/PT_CFM generally implies that
			 * we're either abandoning the pending system
			 * call or that we defer it's re-execution
			 * (e.g., due to GDB doing an inferior
			 * function call).
			 */
			urbs_end = ia64_get_user_rbs_end(target, pt, &cfm);
			if (write_access) {
				if (*data != urbs_end) {
					if (in_syscall(pt))
						convert_to_non_syscall(target,
								       pt,
								       cfm);
					/*
					 * Simulate user-level write
					 * of ar.bsp:
					 */
					pt->loadrs = 0;
					pt->ar_bspstore = *data;
				}
			} else
				*data = urbs_end;
			return 0;
		case ELF_AR_BSPSTORE_OFFSET:
			ptr = &pt->ar_bspstore;
			break;
		case ELF_AR_RNAT_OFFSET:
			ptr = &pt->ar_rnat;
			break;
		case ELF_AR_CCV_OFFSET:
			ptr = &pt->ar_ccv;
			break;
		case ELF_AR_UNAT_OFFSET:
			ptr = &pt->ar_unat;
			break;
		case ELF_AR_FPSR_OFFSET:
			ptr = &pt->ar_fpsr;
			break;
		case ELF_AR_PFS_OFFSET:
			ptr = &pt->ar_pfs;
			break;
		case ELF_AR_LC_OFFSET:
			return unw_access_ar(info, UNW_AR_LC, data,
					     write_access);
		case ELF_AR_EC_OFFSET:
			return unw_access_ar(info, UNW_AR_EC, data,
					     write_access);
		case ELF_AR_CSD_OFFSET:
			ptr = &pt->ar_csd;
			break;
		case ELF_AR_SSD_OFFSET:
			ptr = &pt->ar_ssd;
		}
	} else if (addr >= ELF_CR_IIP_OFFSET && addr <= ELF_CR_IPSR_OFFSET) {
		switch (addr) {
		case ELF_CR_IIP_OFFSET:
			ptr = &pt->cr_iip;
			break;
		case ELF_CFM_OFFSET:
			urbs_end = ia64_get_user_rbs_end(target, pt, &cfm);
			if (write_access) {
				if (((cfm ^ *data) & PFM_MASK) != 0) {
					if (in_syscall(pt))
						convert_to_non_syscall(target,
								       pt,
								       cfm);
					pt->cr_ifs = ((pt->cr_ifs & ~PFM_MASK)
						      | (*data & PFM_MASK));
				}
			} else
				*data = cfm;
			return 0;
		case ELF_CR_IPSR_OFFSET:
			if (write_access) {
				unsigned long tmp = *data;
				/* psr.ri==3 is a reserved value: SDM 2:25 */
				if ((tmp & IA64_PSR_RI) == IA64_PSR_RI)
					tmp &= ~IA64_PSR_RI;
				pt->cr_ipsr = ((tmp & IPSR_MASK)
					       | (pt->cr_ipsr & ~IPSR_MASK));
			} else
				*data = (pt->cr_ipsr & IPSR_MASK);
			return 0;
		}
	} else if (addr == ELF_NAT_OFFSET)
		return access_nat_bits(target, pt, info,
				       data, write_access);
	else if (addr == ELF_PR_OFFSET)
		ptr = &pt->pr;
	else
		return -1;

	if (write_access)
		*ptr = *data;
	else
		*data = *ptr;

	return 0;
}