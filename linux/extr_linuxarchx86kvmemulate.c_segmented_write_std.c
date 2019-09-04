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
typedef  int /*<<< orphan*/  ulong ;
struct x86_emulate_ctxt {int /*<<< orphan*/  exception; TYPE_1__* ops; } ;
struct segmented_address {int dummy; } ;
struct TYPE_2__ {int (* write_std ) (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 int linearize (struct x86_emulate_ctxt*,struct segmented_address,unsigned int,int,int /*<<< orphan*/ *) ; 
 int stub1 (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int segmented_write_std(struct x86_emulate_ctxt *ctxt,
			       struct segmented_address addr,
			       void *data,
			       unsigned int size)
{
	int rc;
	ulong linear;

	rc = linearize(ctxt, addr, size, true, &linear);
	if (rc != X86EMUL_CONTINUE)
		return rc;
	return ctxt->ops->write_std(ctxt, linear, data, size, &ctxt->exception, false);
}