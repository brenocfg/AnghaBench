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
struct lowcore {int mcesad; } ;

/* Variables and functions */
 int MCESA_ORIGIN_MASK ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mcesa_cache ; 
 int /*<<< orphan*/  nmi_needs_mcesa () ; 

void nmi_free_per_cpu(struct lowcore *lc)
{
	if (!nmi_needs_mcesa())
		return;
	kmem_cache_free(mcesa_cache, (void *)(lc->mcesad & MCESA_ORIGIN_MASK));
}