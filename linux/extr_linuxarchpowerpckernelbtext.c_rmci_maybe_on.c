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

__attribute__((used)) static inline void rmci_maybe_on(void)
{
#if defined(CONFIG_PPC_EARLY_DEBUG_BOOTX) && defined(CONFIG_PPC64)
	if (!(mfmsr() & MSR_DR))
		rmci_on();
#endif
}