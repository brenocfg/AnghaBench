#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct parsed_partitions {int /*<<< orphan*/  bdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  partition_entry_array_crc32; int /*<<< orphan*/  sizeof_partition_entry; int /*<<< orphan*/  num_partition_entries; int /*<<< orphan*/  first_usable_lba; int /*<<< orphan*/  last_usable_lba; int /*<<< orphan*/  my_lba; int /*<<< orphan*/  header_crc32; int /*<<< orphan*/  header_size; int /*<<< orphan*/  signature; } ;
typedef  TYPE_1__ gpt_header ;
typedef  TYPE_1__ gpt_entry ;

/* Variables and functions */
 scalar_t__ GPT_HEADER_SIGNATURE ; 
 scalar_t__ KMALLOC_MAX_SIZE ; 
 TYPE_1__* alloc_read_gpt_entries (struct parsed_partitions*,TYPE_1__*) ; 
 TYPE_1__* alloc_read_gpt_header (struct parsed_partitions*,scalar_t__) ; 
 scalar_t__ bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ efi_crc32 (unsigned char const*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 scalar_t__ last_lba (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int is_gpt_valid(struct parsed_partitions *state, u64 lba,
			gpt_header **gpt, gpt_entry **ptes)
{
	u32 crc, origcrc;
	u64 lastlba, pt_size;

	if (!ptes)
		return 0;
	if (!(*gpt = alloc_read_gpt_header(state, lba)))
		return 0;

	/* Check the GUID Partition Table signature */
	if (le64_to_cpu((*gpt)->signature) != GPT_HEADER_SIGNATURE) {
		pr_debug("GUID Partition Table Header signature is wrong:"
			 "%lld != %lld\n",
			 (unsigned long long)le64_to_cpu((*gpt)->signature),
			 (unsigned long long)GPT_HEADER_SIGNATURE);
		goto fail;
	}

	/* Check the GUID Partition Table header size is too big */
	if (le32_to_cpu((*gpt)->header_size) >
			bdev_logical_block_size(state->bdev)) {
		pr_debug("GUID Partition Table Header size is too large: %u > %u\n",
			le32_to_cpu((*gpt)->header_size),
			bdev_logical_block_size(state->bdev));
		goto fail;
	}

	/* Check the GUID Partition Table header size is too small */
	if (le32_to_cpu((*gpt)->header_size) < sizeof(gpt_header)) {
		pr_debug("GUID Partition Table Header size is too small: %u < %zu\n",
			le32_to_cpu((*gpt)->header_size),
			sizeof(gpt_header));
		goto fail;
	}

	/* Check the GUID Partition Table CRC */
	origcrc = le32_to_cpu((*gpt)->header_crc32);
	(*gpt)->header_crc32 = 0;
	crc = efi_crc32((const unsigned char *) (*gpt), le32_to_cpu((*gpt)->header_size));

	if (crc != origcrc) {
		pr_debug("GUID Partition Table Header CRC is wrong: %x != %x\n",
			 crc, origcrc);
		goto fail;
	}
	(*gpt)->header_crc32 = cpu_to_le32(origcrc);

	/* Check that the my_lba entry points to the LBA that contains
	 * the GUID Partition Table */
	if (le64_to_cpu((*gpt)->my_lba) != lba) {
		pr_debug("GPT my_lba incorrect: %lld != %lld\n",
			 (unsigned long long)le64_to_cpu((*gpt)->my_lba),
			 (unsigned long long)lba);
		goto fail;
	}

	/* Check the first_usable_lba and last_usable_lba are
	 * within the disk.
	 */
	lastlba = last_lba(state->bdev);
	if (le64_to_cpu((*gpt)->first_usable_lba) > lastlba) {
		pr_debug("GPT: first_usable_lba incorrect: %lld > %lld\n",
			 (unsigned long long)le64_to_cpu((*gpt)->first_usable_lba),
			 (unsigned long long)lastlba);
		goto fail;
	}
	if (le64_to_cpu((*gpt)->last_usable_lba) > lastlba) {
		pr_debug("GPT: last_usable_lba incorrect: %lld > %lld\n",
			 (unsigned long long)le64_to_cpu((*gpt)->last_usable_lba),
			 (unsigned long long)lastlba);
		goto fail;
	}
	if (le64_to_cpu((*gpt)->last_usable_lba) < le64_to_cpu((*gpt)->first_usable_lba)) {
		pr_debug("GPT: last_usable_lba incorrect: %lld > %lld\n",
			 (unsigned long long)le64_to_cpu((*gpt)->last_usable_lba),
			 (unsigned long long)le64_to_cpu((*gpt)->first_usable_lba));
		goto fail;
	}
	/* Check that sizeof_partition_entry has the correct value */
	if (le32_to_cpu((*gpt)->sizeof_partition_entry) != sizeof(gpt_entry)) {
		pr_debug("GUID Partition Entry Size check failed.\n");
		goto fail;
	}

	/* Sanity check partition table size */
	pt_size = (u64)le32_to_cpu((*gpt)->num_partition_entries) *
		le32_to_cpu((*gpt)->sizeof_partition_entry);
	if (pt_size > KMALLOC_MAX_SIZE) {
		pr_debug("GUID Partition Table is too large: %llu > %lu bytes\n",
			 (unsigned long long)pt_size, KMALLOC_MAX_SIZE);
		goto fail;
	}

	if (!(*ptes = alloc_read_gpt_entries(state, *gpt)))
		goto fail;

	/* Check the GUID Partition Entry Array CRC */
	crc = efi_crc32((const unsigned char *) (*ptes), pt_size);

	if (crc != le32_to_cpu((*gpt)->partition_entry_array_crc32)) {
		pr_debug("GUID Partition Entry Array CRC check failed.\n");
		goto fail_ptes;
	}

	/* We're done, all's well */
	return 1;

 fail_ptes:
	kfree(*ptes);
	*ptes = NULL;
 fail:
	kfree(*gpt);
	*gpt = NULL;
	return 0;
}