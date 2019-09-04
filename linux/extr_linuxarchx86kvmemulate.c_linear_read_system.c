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
struct TYPE_2__ {int (* read_std ) (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int stub1 (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int linear_read_system(struct x86_emulate_ctxt *ctxt, ulong linear,
			      void *data, unsigned size)
{
	return ctxt->ops->read_std(ctxt, linear, data, size, &ctxt->exception, true);
}