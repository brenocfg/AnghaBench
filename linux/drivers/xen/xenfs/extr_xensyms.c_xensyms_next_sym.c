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
typedef  scalar_t__ uint64_t ;
struct xenpf_symdata {scalar_t__ namelen; scalar_t__ symnum; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct xenpf_symdata symdata; } ;
struct TYPE_4__ {TYPE_1__ u; } ;
struct xensyms {scalar_t__ namelen; TYPE_2__ op; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HYPERVISOR_platform_op (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int xensyms_next_sym(struct xensyms *xs)
{
	int ret;
	struct xenpf_symdata *symdata = &xs->op.u.symdata;
	uint64_t symnum;

	memset(xs->name, 0, xs->namelen);
	symdata->namelen = xs->namelen;

	symnum = symdata->symnum;

	ret = HYPERVISOR_platform_op(&xs->op);
	if (ret < 0)
		return ret;

	/*
	 * If hypervisor's symbol didn't fit into the buffer then allocate
	 * a larger buffer and try again.
	 */
	if (unlikely(symdata->namelen > xs->namelen)) {
		kfree(xs->name);

		xs->namelen = symdata->namelen;
		xs->name = kzalloc(xs->namelen, GFP_KERNEL);
		if (!xs->name)
			return -ENOMEM;

		set_xen_guest_handle(symdata->name, xs->name);
		symdata->symnum--; /* Rewind */

		ret = HYPERVISOR_platform_op(&xs->op);
		if (ret < 0)
			return ret;
	}

	if (symdata->symnum == symnum)
		/* End of symbols */
		return 1;

	return 0;
}