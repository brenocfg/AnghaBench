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

__attribute__((used)) static inline void fallback_on_nodma_alloc(char **addr, size_t l)
{
#ifdef FLOPPY_CAN_FALLBACK_ON_NODMA
	if (*addr)
		return;		/* we have the memory */
	if (can_use_virtual_dma != 2)
		return;		/* no fallback allowed */
	pr_info("DMA memory shortage. Temporarily falling back on virtual DMA\n");
	*addr = (char *)nodma_mem_alloc(l);
#else
	return;
#endif
}