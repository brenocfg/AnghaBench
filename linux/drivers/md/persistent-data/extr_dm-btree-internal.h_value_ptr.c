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
struct TYPE_2__ {int /*<<< orphan*/  value_size; } ;
struct btree_node {TYPE_1__ header; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* value_base (struct btree_node*) ; 

__attribute__((used)) static inline void *value_ptr(struct btree_node *n, uint32_t index)
{
	uint32_t value_size = le32_to_cpu(n->header.value_size);
	return value_base(n) + (value_size * index);
}