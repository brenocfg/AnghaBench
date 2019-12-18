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
struct kpc_dma_device {struct kpc_dma_descriptor* desc_completed; struct kpc_dma_descriptor* desc_next; } ;
struct kpc_dma_descriptor {struct kpc_dma_descriptor* Next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 

int  count_descriptors_available(struct kpc_dma_device *eng)
{
	u32 count = 0;
	struct kpc_dma_descriptor *cur = eng->desc_next;

	while (cur != eng->desc_completed) {
		BUG_ON(cur == NULL);
		count++;
		cur = cur->Next;
	}
	return count;
}