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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct smem_ptable_entry {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct smem_partition_header {int /*<<< orphan*/  offset_free_uncached; int /*<<< orphan*/  size; int /*<<< orphan*/  host1; int /*<<< orphan*/  host0; int /*<<< orphan*/ * magic; } ;
struct qcom_smem {int /*<<< orphan*/  dev; TYPE_1__* regions; } ;
struct TYPE_2__ {struct smem_partition_header* virt_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMEM_PART_MAGIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct smem_partition_header *
qcom_smem_partition_header(struct qcom_smem *smem,
		struct smem_ptable_entry *entry, u16 host0, u16 host1)
{
	struct smem_partition_header *header;
	u32 size;

	header = smem->regions[0].virt_base + le32_to_cpu(entry->offset);

	if (memcmp(header->magic, SMEM_PART_MAGIC, sizeof(header->magic))) {
		dev_err(smem->dev, "bad partition magic %02x %02x %02x %02x\n",
			header->magic[0], header->magic[1],
			header->magic[2], header->magic[3]);
		return NULL;
	}

	if (host0 != le16_to_cpu(header->host0)) {
		dev_err(smem->dev, "bad host0 (%hu != %hu)\n",
				host0, le16_to_cpu(header->host0));
		return NULL;
	}
	if (host1 != le16_to_cpu(header->host1)) {
		dev_err(smem->dev, "bad host1 (%hu != %hu)\n",
				host1, le16_to_cpu(header->host1));
		return NULL;
	}

	size = le32_to_cpu(header->size);
	if (size != le32_to_cpu(entry->size)) {
		dev_err(smem->dev, "bad partition size (%u != %u)\n",
			size, le32_to_cpu(entry->size));
		return NULL;
	}

	if (le32_to_cpu(header->offset_free_uncached) > size) {
		dev_err(smem->dev, "bad partition free uncached (%u > %u)\n",
			le32_to_cpu(header->offset_free_uncached), size);
		return NULL;
	}

	return header;
}