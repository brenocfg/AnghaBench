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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {scalar_t__ val; } ;
struct x86_emulate_ctxt {TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_NONE ; 
 int /*<<< orphan*/  em_bsr ; 
 int fastop (struct x86_emulate_ctxt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em_bsr_c(struct x86_emulate_ctxt *ctxt)
{
	/* If src is zero, do not writeback, but update flags */
	if (ctxt->src.val == 0)
		ctxt->dst.type = OP_NONE;
	return fastop(ctxt, em_bsr);
}