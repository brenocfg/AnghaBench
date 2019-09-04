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
struct btree_keys {size_t page_order; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 

__attribute__((used)) static inline size_t btree_keys_bytes(struct btree_keys *b)
{
	return PAGE_SIZE << b->page_order;
}