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
typedef  scalar_t__ u32 ;
struct siw_uobj {scalar_t__ size; } ;
struct siw_ucontext {int /*<<< orphan*/  xa; } ;

/* Variables and functions */
 struct siw_uobj* xa_load (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct siw_uobj *siw_get_uobj(struct siw_ucontext *uctx,
				     unsigned long off, u32 size)
{
	struct siw_uobj *uobj = xa_load(&uctx->xa, off);

	if (uobj && uobj->size == size)
		return uobj;

	return NULL;
}