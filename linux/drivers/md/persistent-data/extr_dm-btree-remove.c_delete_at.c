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
typedef  unsigned int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  value_size; } ;
struct btree_node {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  key_ptr (struct btree_node*,unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  value_ptr (struct btree_node*,unsigned int) ; 

__attribute__((used)) static void delete_at(struct btree_node *n, unsigned index)
{
	unsigned nr_entries = le32_to_cpu(n->header.nr_entries);
	unsigned nr_to_copy = nr_entries - (index + 1);
	uint32_t value_size = le32_to_cpu(n->header.value_size);
	BUG_ON(index >= nr_entries);

	if (nr_to_copy) {
		memmove(key_ptr(n, index),
			key_ptr(n, index + 1),
			nr_to_copy * sizeof(__le64));

		memmove(value_ptr(n, index),
			value_ptr(n, index + 1),
			nr_to_copy * value_size);
	}

	n->header.nr_entries = cpu_to_le32(nr_entries - 1);
}