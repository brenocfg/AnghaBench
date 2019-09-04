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
struct lowcore {unsigned long mcesad; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_not_leak (void*) ; 
 int /*<<< orphan*/  mcesa_cache ; 
 unsigned long mcesa_origin_lc ; 
 int /*<<< orphan*/  nmi_needs_mcesa () ; 

int nmi_alloc_per_cpu(struct lowcore *lc)
{
	unsigned long origin;

	if (!nmi_needs_mcesa())
		return 0;
	origin = (unsigned long) kmem_cache_alloc(mcesa_cache, GFP_KERNEL);
	if (!origin)
		return -ENOMEM;
	/* The pointer is stored with mcesa_bits ORed in */
	kmemleak_not_leak((void *) origin);
	lc->mcesad = origin | mcesa_origin_lc;
	return 0;
}