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
 void* key_ptr (struct btree_node*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 
 void* value_ptr (struct btree_node*,int) ; 

__attribute__((used)) static void node_shift(struct btree_node *n, int shift)
{
	uint32_t nr_entries = le32_to_cpu(n->header.nr_entries);
	uint32_t value_size = le32_to_cpu(n->header.value_size);

	if (shift < 0) {
		shift = -shift;
		BUG_ON(shift > nr_entries);
		BUG_ON((void *) key_ptr(n, shift) >= value_ptr(n, shift));
		memmove(key_ptr(n, 0),
			key_ptr(n, shift),
			(nr_entries - shift) * sizeof(__le64));
		memmove(value_ptr(n, 0),
			value_ptr(n, shift),
			(nr_entries - shift) * value_size);
	} else {
		BUG_ON(nr_entries + shift > le32_to_cpu(n->header.max_entries));
		memmove(key_ptr(n, shift),
			key_ptr(n, 0),
			nr_entries * sizeof(__le64));
		memmove(value_ptr(n, shift),
			value_ptr(n, 0),
			nr_entries * value_size);
	}
}