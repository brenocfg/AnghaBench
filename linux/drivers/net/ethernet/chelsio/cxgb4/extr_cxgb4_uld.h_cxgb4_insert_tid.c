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
struct tid_info {unsigned int hash_base; int /*<<< orphan*/  conns_in_use; int /*<<< orphan*/  tids_in_use; int /*<<< orphan*/  hash_tids_in_use; void** tid_tab; } ;

/* Variables and functions */
 unsigned short AF_INET6 ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cxgb4_insert_tid(struct tid_info *t, void *data,
				    unsigned int tid, unsigned short family)
{
	t->tid_tab[tid] = data;
	if (t->hash_base && (tid >= t->hash_base)) {
		if (family == AF_INET6)
			atomic_add(2, &t->hash_tids_in_use);
		else
			atomic_inc(&t->hash_tids_in_use);
	} else {
		if (family == AF_INET6)
			atomic_add(2, &t->tids_in_use);
		else
			atomic_inc(&t->tids_in_use);
	}
	atomic_inc(&t->conns_in_use);
}