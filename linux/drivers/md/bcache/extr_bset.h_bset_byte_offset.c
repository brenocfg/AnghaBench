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
struct btree_keys {TYPE_1__* set; } ;
struct bset {int dummy; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int bset_byte_offset(struct btree_keys *b,
					    struct bset *i)
{
	return ((size_t) i) - ((size_t) b->set->data);
}