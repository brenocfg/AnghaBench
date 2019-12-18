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
struct smem_private_entry {scalar_t__ canary; scalar_t__ padding_hdr; int /*<<< orphan*/  size; void* padding_data; void* item; } ;
struct smem_partition_header {void* host1; void* host0; int /*<<< orphan*/  offset_free_uncached; } ;
struct qcom_smem {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALIGN (size_t,int) ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ SMEM_PRIVATE_CANARY ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,size_t) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct smem_private_entry* phdr_to_first_uncached_entry (struct smem_partition_header*) ; 
 void* phdr_to_last_cached_entry (struct smem_partition_header*) ; 
 struct smem_private_entry* phdr_to_last_uncached_entry (struct smem_partition_header*) ; 
 struct smem_private_entry* uncached_entry_next (struct smem_private_entry*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int qcom_smem_alloc_private(struct qcom_smem *smem,
				   struct smem_partition_header *phdr,
				   unsigned item,
				   size_t size)
{
	struct smem_private_entry *hdr, *end;
	size_t alloc_size;
	void *cached;

	hdr = phdr_to_first_uncached_entry(phdr);
	end = phdr_to_last_uncached_entry(phdr);
	cached = phdr_to_last_cached_entry(phdr);

	while (hdr < end) {
		if (hdr->canary != SMEM_PRIVATE_CANARY)
			goto bad_canary;
		if (le16_to_cpu(hdr->item) == item)
			return -EEXIST;

		hdr = uncached_entry_next(hdr);
	}

	/* Check that we don't grow into the cached region */
	alloc_size = sizeof(*hdr) + ALIGN(size, 8);
	if ((void *)hdr + alloc_size > cached) {
		dev_err(smem->dev, "Out of memory\n");
		return -ENOSPC;
	}

	hdr->canary = SMEM_PRIVATE_CANARY;
	hdr->item = cpu_to_le16(item);
	hdr->size = cpu_to_le32(ALIGN(size, 8));
	hdr->padding_data = cpu_to_le16(le32_to_cpu(hdr->size) - size);
	hdr->padding_hdr = 0;

	/*
	 * Ensure the header is written before we advance the free offset, so
	 * that remote processors that does not take the remote spinlock still
	 * gets a consistent view of the linked list.
	 */
	wmb();
	le32_add_cpu(&phdr->offset_free_uncached, alloc_size);

	return 0;
bad_canary:
	dev_err(smem->dev, "Found invalid canary in hosts %hu:%hu partition\n",
		le16_to_cpu(phdr->host0), le16_to_cpu(phdr->host1));

	return -EINVAL;
}