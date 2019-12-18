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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_entries; int /*<<< orphan*/  value_size; int /*<<< orphan*/  nr_entries; } ;
struct btree_node {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  key_ptr (struct btree_node*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  value_ptr (struct btree_node*,int) ; 

__attribute__((used)) static void node_copy(struct btree_node *left, struct btree_node *right, int shift)
{
	uint32_t nr_left = le32_to_cpu(left->header.nr_entries);
	uint32_t value_size = le32_to_cpu(left->header.value_size);
	BUG_ON(value_size != le32_to_cpu(right->header.value_size));

	if (shift < 0) {
		shift = -shift;
		BUG_ON(nr_left + shift > le32_to_cpu(left->header.max_entries));
		memcpy(key_ptr(left, nr_left),
		       key_ptr(right, 0),
		       shift * sizeof(__le64));
		memcpy(value_ptr(left, nr_left),
		       value_ptr(right, 0),
		       shift * value_size);
	} else {
		BUG_ON(shift > le32_to_cpu(right->header.max_entries));
		memcpy(key_ptr(right, 0),
		       key_ptr(left, nr_left - shift),
		       shift * sizeof(__le64));
		memcpy(value_ptr(right, 0),
		       value_ptr(left, nr_left - shift),
		       shift * value_size);
	}
}