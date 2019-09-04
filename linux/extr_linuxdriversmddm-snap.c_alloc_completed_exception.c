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
struct dm_exception {int dummy; } ;
typedef  scalar_t__ gfp_t ;

/* Variables and functions */
 scalar_t__ GFP_ATOMIC ; 
 scalar_t__ GFP_NOIO ; 
 int /*<<< orphan*/  exception_cache ; 
 struct dm_exception* kmem_cache_alloc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct dm_exception *alloc_completed_exception(gfp_t gfp)
{
	struct dm_exception *e;

	e = kmem_cache_alloc(exception_cache, gfp);
	if (!e && gfp == GFP_NOIO)
		e = kmem_cache_alloc(exception_cache, GFP_ATOMIC);

	return e;
}