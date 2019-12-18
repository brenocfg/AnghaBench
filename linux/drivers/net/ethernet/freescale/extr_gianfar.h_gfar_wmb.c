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

/* Variables and functions */
 int /*<<< orphan*/  eieio () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void gfar_wmb(void)
{
#if defined(CONFIG_PPC)
	/* The powerpc-specific eieio() is used, as wmb() has too strong
	 * semantics (it requires synchronization between cacheable and
	 * uncacheable mappings, which eieio() doesn't provide and which we
	 * don't need), thus requiring a more expensive sync instruction.  At
	 * some point, the set of architecture-independent barrier functions
	 * should be expanded to include weaker barriers.
	 */
	eieio();
#else
	wmb(); /* order write acesses for BD (or FCB) fields */
#endif
}