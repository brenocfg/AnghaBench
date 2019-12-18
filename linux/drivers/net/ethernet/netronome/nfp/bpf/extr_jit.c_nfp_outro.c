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
struct nfp_prog {int type; } ;

/* Variables and functions */
#define  BPF_PROG_TYPE_SCHED_CLS 129 
#define  BPF_PROG_TYPE_XDP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  nfp_outro_tc_da (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_outro_xdp (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_pop_callee_registers (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_prog_needs_callee_reg_save (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_push_callee_registers (struct nfp_prog*) ; 

__attribute__((used)) static void nfp_outro(struct nfp_prog *nfp_prog)
{
	switch (nfp_prog->type) {
	case BPF_PROG_TYPE_SCHED_CLS:
		nfp_outro_tc_da(nfp_prog);
		break;
	case BPF_PROG_TYPE_XDP:
		nfp_outro_xdp(nfp_prog);
		break;
	default:
		WARN_ON(1);
	}

	if (!nfp_prog_needs_callee_reg_save(nfp_prog))
		return;

	nfp_push_callee_registers(nfp_prog);
	nfp_pop_callee_registers(nfp_prog);
}