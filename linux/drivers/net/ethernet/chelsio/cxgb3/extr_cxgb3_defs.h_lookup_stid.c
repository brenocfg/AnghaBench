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
struct t3c_tid_entry {int dummy; } ;
union listen_entry {struct t3c_tid_entry t3c_tid; scalar_t__ next; } ;
struct tid_info {unsigned int stid_base; unsigned int nstids; size_t natids; int /*<<< orphan*/ * atid_tab; scalar_t__ tid_tab; } ;

/* Variables and functions */
 union listen_entry* stid2entry (struct tid_info const*,unsigned int) ; 

__attribute__((used)) static inline struct t3c_tid_entry *lookup_stid(const struct tid_info *t,
						unsigned int tid)
{
	union listen_entry *e;

	if (tid < t->stid_base || tid >= t->stid_base + t->nstids)
		return NULL;

	e = stid2entry(t, tid);
	if ((void *)e->next >= (void *)t->tid_tab &&
	    (void *)e->next < (void *)&t->atid_tab[t->natids])
		return NULL;

	return &e->t3c_tid;
}