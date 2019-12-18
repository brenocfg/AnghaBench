#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smem_header {int /*<<< orphan*/  available; int /*<<< orphan*/  free_offset; struct smem_global_entry* toc; } ;
struct smem_global_entry {void* allocated; void* size; int /*<<< orphan*/  offset; } ;
struct qcom_smem {TYPE_1__* regions; } ;
struct TYPE_2__ {struct smem_header* virt_base; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int EEXIST ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,size_t) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int qcom_smem_alloc_global(struct qcom_smem *smem,
				  unsigned item,
				  size_t size)
{
	struct smem_global_entry *entry;
	struct smem_header *header;

	header = smem->regions[0].virt_base;
	entry = &header->toc[item];
	if (entry->allocated)
		return -EEXIST;

	size = ALIGN(size, 8);
	if (WARN_ON(size > le32_to_cpu(header->available)))
		return -ENOMEM;

	entry->offset = header->free_offset;
	entry->size = cpu_to_le32(size);

	/*
	 * Ensure the header is consistent before we mark the item allocated,
	 * so that remote processors will get a consistent view of the item
	 * even though they do not take the spinlock on read.
	 */
	wmb();
	entry->allocated = cpu_to_le32(1);

	le32_add_cpu(&header->free_offset, size);
	le32_add_cpu(&header->available, -size);

	return 0;
}