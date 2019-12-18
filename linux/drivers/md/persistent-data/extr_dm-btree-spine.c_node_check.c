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
typedef  int uint32_t ;
struct node_header {scalar_t__ flags; scalar_t__ csum; scalar_t__ value_size; scalar_t__ max_entries; scalar_t__ nr_entries; int /*<<< orphan*/  blocknr; } ;
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
struct btree_node {struct node_header header; } ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTREE_CSUM_XOR ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*,...) ; 
 int EILSEQ ; 
 int ENOTBLK ; 
 int INTERNAL_NODE ; 
 int LEAF_NODE ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct btree_node* dm_block_data (struct dm_block*) ; 
 scalar_t__ dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_checksum (scalar_t__*,size_t,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int node_check(struct dm_block_validator *v,
		      struct dm_block *b,
		      size_t block_size)
{
	struct btree_node *n = dm_block_data(b);
	struct node_header *h = &n->header;
	size_t value_size;
	__le32 csum_disk;
	uint32_t flags;

	if (dm_block_location(b) != le64_to_cpu(h->blocknr)) {
		DMERR_LIMIT("node_check failed: blocknr %llu != wanted %llu",
			    le64_to_cpu(h->blocknr), dm_block_location(b));
		return -ENOTBLK;
	}

	csum_disk = cpu_to_le32(dm_bm_checksum(&h->flags,
					       block_size - sizeof(__le32),
					       BTREE_CSUM_XOR));
	if (csum_disk != h->csum) {
		DMERR_LIMIT("node_check failed: csum %u != wanted %u",
			    le32_to_cpu(csum_disk), le32_to_cpu(h->csum));
		return -EILSEQ;
	}

	value_size = le32_to_cpu(h->value_size);

	if (sizeof(struct node_header) +
	    (sizeof(__le64) + value_size) * le32_to_cpu(h->max_entries) > block_size) {
		DMERR_LIMIT("node_check failed: max_entries too large");
		return -EILSEQ;
	}

	if (le32_to_cpu(h->nr_entries) > le32_to_cpu(h->max_entries)) {
		DMERR_LIMIT("node_check failed: too many entries");
		return -EILSEQ;
	}

	/*
	 * The node must be either INTERNAL or LEAF.
	 */
	flags = le32_to_cpu(h->flags);
	if (!(flags & INTERNAL_NODE) && !(flags & LEAF_NODE)) {
		DMERR_LIMIT("node_check failed: node is neither INTERNAL or LEAF");
		return -EILSEQ;
	}

	return 0;
}