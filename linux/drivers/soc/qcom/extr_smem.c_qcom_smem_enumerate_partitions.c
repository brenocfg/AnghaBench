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
typedef  unsigned int u16 ;
struct smem_ptable_entry {int /*<<< orphan*/  cacheline; int /*<<< orphan*/  host1; int /*<<< orphan*/  host0; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct smem_ptable {struct smem_ptable_entry* entry; int /*<<< orphan*/  num_entries; } ;
struct smem_partition_header {int dummy; } ;
struct qcom_smem {int* cacheline; struct smem_partition_header** partitions; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct smem_ptable*) ; 
 int PTR_ERR (struct smem_ptable*) ; 
 unsigned int SMEM_HOST_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct smem_ptable* qcom_smem_get_ptable (struct qcom_smem*) ; 
 struct smem_partition_header* qcom_smem_partition_header (struct qcom_smem*,struct smem_ptable_entry*,unsigned int,unsigned int) ; 

__attribute__((used)) static int
qcom_smem_enumerate_partitions(struct qcom_smem *smem, u16 local_host)
{
	struct smem_partition_header *header;
	struct smem_ptable_entry *entry;
	struct smem_ptable *ptable;
	unsigned int remote_host;
	u16 host0, host1;
	int i;

	ptable = qcom_smem_get_ptable(smem);
	if (IS_ERR(ptable))
		return PTR_ERR(ptable);

	for (i = 0; i < le32_to_cpu(ptable->num_entries); i++) {
		entry = &ptable->entry[i];
		if (!le32_to_cpu(entry->offset))
			continue;
		if (!le32_to_cpu(entry->size))
			continue;

		host0 = le16_to_cpu(entry->host0);
		host1 = le16_to_cpu(entry->host1);
		if (host0 == local_host)
			remote_host = host1;
		else if (host1 == local_host)
			remote_host = host0;
		else
			continue;

		if (remote_host >= SMEM_HOST_COUNT) {
			dev_err(smem->dev, "bad host %hu\n", remote_host);
			return -EINVAL;
		}

		if (smem->partitions[remote_host]) {
			dev_err(smem->dev, "duplicate host %hu\n", remote_host);
			return -EINVAL;
		}

		header = qcom_smem_partition_header(smem, entry, host0, host1);
		if (!header)
			return -EINVAL;

		smem->partitions[remote_host] = header;
		smem->cacheline[remote_host] = le32_to_cpu(entry->cacheline);
	}

	return 0;
}