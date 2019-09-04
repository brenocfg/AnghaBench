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
struct btree_keys {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool btree_keys_expensive_checks(struct btree_keys *b)
{
#ifdef CONFIG_BCACHE_DEBUG
	return *b->expensive_debug_checks;
#else
	return false;
#endif
}