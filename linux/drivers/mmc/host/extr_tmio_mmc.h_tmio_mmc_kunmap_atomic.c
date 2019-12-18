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
struct scatterlist {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 

__attribute__((used)) static inline void tmio_mmc_kunmap_atomic(struct scatterlist *sg,
					  unsigned long *flags, void *virt)
{
	kunmap_atomic(virt - sg->offset);
	local_irq_restore(*flags);
}