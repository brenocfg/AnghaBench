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
typedef  int u32 ;
struct xa_limit {int dummy; } ;
struct siw_mem {int stag; } ;
struct siw_device {int /*<<< orphan*/  mem_xa; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xa_limit XA_LIMIT (int,int) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  siw_dbg_mem (struct siw_mem*,char*) ; 
 scalar_t__ xa_alloc_cyclic (int /*<<< orphan*/ *,int*,struct siw_mem*,struct xa_limit,int*,int /*<<< orphan*/ ) ; 

int siw_mem_add(struct siw_device *sdev, struct siw_mem *m)
{
	struct xa_limit limit = XA_LIMIT(1, 0x00ffffff);
	u32 id, next;

	get_random_bytes(&next, 4);
	next &= 0x00ffffff;

	if (xa_alloc_cyclic(&sdev->mem_xa, &id, m, limit, &next,
	    GFP_KERNEL) < 0)
		return -ENOMEM;

	/* Set the STag index part */
	m->stag = id << 8;

	siw_dbg_mem(m, "new MEM object\n");

	return 0;
}