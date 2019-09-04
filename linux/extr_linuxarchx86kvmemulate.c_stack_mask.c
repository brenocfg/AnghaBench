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
typedef  unsigned long ulong ;
typedef  int /*<<< orphan*/  u16 ;
struct x86_emulate_ctxt {scalar_t__ mode; TYPE_1__* ops; } ;
struct desc_struct {int d; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_segment ) (struct x86_emulate_ctxt*,int /*<<< orphan*/ *,struct desc_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_SREG_SS ; 
 scalar_t__ X86EMUL_MODE_PROT64 ; 
 int /*<<< orphan*/  stub1 (struct x86_emulate_ctxt*,int /*<<< orphan*/ *,struct desc_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ulong stack_mask(struct x86_emulate_ctxt *ctxt)
{
	u16 sel;
	struct desc_struct ss;

	if (ctxt->mode == X86EMUL_MODE_PROT64)
		return ~0UL;
	ctxt->ops->get_segment(ctxt, &sel, &ss, NULL, VCPU_SREG_SS);
	return ~0U >> ((ss.d ^ 1) * 16);  /* d=0: 0xffff; d=1: 0xffffffff */
}