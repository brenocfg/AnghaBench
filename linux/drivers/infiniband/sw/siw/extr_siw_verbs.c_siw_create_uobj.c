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
typedef  int /*<<< orphan*/  u32 ;
struct xa_limit {int dummy; } ;
struct siw_uobj {void* addr; int /*<<< orphan*/  size; } ;
struct siw_ucontext {int /*<<< orphan*/  uobj_nextkey; int /*<<< orphan*/  xa; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIW_INVAL_UOBJ_KEY ; 
 int /*<<< orphan*/  SIW_UOBJ_MAX_KEY ; 
 struct xa_limit XA_LIMIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct siw_uobj*) ; 
 struct siw_uobj* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ xa_alloc_cyclic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct siw_uobj*,struct xa_limit,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 siw_create_uobj(struct siw_ucontext *uctx, void *vaddr, u32 size)
{
	struct siw_uobj *uobj;
	struct xa_limit limit = XA_LIMIT(0, SIW_UOBJ_MAX_KEY);
	u32 key;

	uobj = kzalloc(sizeof(*uobj), GFP_KERNEL);
	if (!uobj)
		return SIW_INVAL_UOBJ_KEY;

	if (xa_alloc_cyclic(&uctx->xa, &key, uobj, limit, &uctx->uobj_nextkey,
			    GFP_KERNEL) < 0) {
		kfree(uobj);
		return SIW_INVAL_UOBJ_KEY;
	}
	uobj->size = PAGE_ALIGN(size);
	uobj->addr = vaddr;

	return key;
}