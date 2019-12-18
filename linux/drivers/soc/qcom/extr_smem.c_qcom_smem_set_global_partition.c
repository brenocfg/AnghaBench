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
struct smem_ptable_entry {int /*<<< orphan*/  cacheline; int /*<<< orphan*/  host1; int /*<<< orphan*/  host0; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct smem_ptable {struct smem_ptable_entry* entry; int /*<<< orphan*/  num_entries; } ;
struct smem_partition_header {int dummy; } ;
struct qcom_smem {int global_cacheline; struct smem_partition_header* global_partition; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct smem_ptable*) ; 
 int PTR_ERR (struct smem_ptable*) ; 
 scalar_t__ SMEM_GLOBAL_HOST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct smem_ptable* qcom_smem_get_ptable (struct qcom_smem*) ; 
 struct smem_partition_header* qcom_smem_partition_header (struct qcom_smem*,struct smem_ptable_entry*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int qcom_smem_set_global_partition(struct qcom_smem *smem)
{
	struct smem_partition_header *header;
	struct smem_ptable_entry *entry;
	struct smem_ptable *ptable;
	bool found = false;
	int i;

	if (smem->global_partition) {
		dev_err(smem->dev, "Already found the global partition\n");
		return -EINVAL;
	}

	ptable = qcom_smem_get_ptable(smem);
	if (IS_ERR(ptable))
		return PTR_ERR(ptable);

	for (i = 0; i < le32_to_cpu(ptable->num_entries); i++) {
		entry = &ptable->entry[i];
		if (!le32_to_cpu(entry->offset))
			continue;
		if (!le32_to_cpu(entry->size))
			continue;

		if (le16_to_cpu(entry->host0) != SMEM_GLOBAL_HOST)
			continue;

		if (le16_to_cpu(entry->host1) == SMEM_GLOBAL_HOST) {
			found = true;
			break;
		}
	}

	if (!found) {
		dev_err(smem->dev, "Missing entry for global partition\n");
		return -EINVAL;
	}

	header = qcom_smem_partition_header(smem, entry,
				SMEM_GLOBAL_HOST, SMEM_GLOBAL_HOST);
	if (!header)
		return -EINVAL;

	smem->global_partition = header;
	smem->global_cacheline = le32_to_cpu(entry->cacheline);

	return 0;
}