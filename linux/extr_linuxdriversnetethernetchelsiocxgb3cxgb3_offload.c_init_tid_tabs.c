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
union listen_entry {union listen_entry* next; } ;
union active_open_entry {union active_open_entry* next; } ;
struct tid_info {unsigned int ntids; unsigned int nstids; unsigned int stid_base; unsigned int natids; unsigned int atid_base; union active_open_entry* atid_tab; union active_open_entry* afree; union listen_entry* stid_tab; union listen_entry* sfree; int /*<<< orphan*/  atid_lock; int /*<<< orphan*/  stid_lock; int /*<<< orphan*/  tids_in_use; scalar_t__ atids_in_use; scalar_t__ stids_in_use; int /*<<< orphan*/ * tid_tab; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kvzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_tid_tabs(struct tid_info *t, unsigned int ntids,
			 unsigned int natids, unsigned int nstids,
			 unsigned int atid_base, unsigned int stid_base)
{
	unsigned long size = ntids * sizeof(*t->tid_tab) +
	    natids * sizeof(*t->atid_tab) + nstids * sizeof(*t->stid_tab);

	t->tid_tab = kvzalloc(size, GFP_KERNEL);
	if (!t->tid_tab)
		return -ENOMEM;

	t->stid_tab = (union listen_entry *)&t->tid_tab[ntids];
	t->atid_tab = (union active_open_entry *)&t->stid_tab[nstids];
	t->ntids = ntids;
	t->nstids = nstids;
	t->stid_base = stid_base;
	t->sfree = NULL;
	t->natids = natids;
	t->atid_base = atid_base;
	t->afree = NULL;
	t->stids_in_use = t->atids_in_use = 0;
	atomic_set(&t->tids_in_use, 0);
	spin_lock_init(&t->stid_lock);
	spin_lock_init(&t->atid_lock);

	/*
	 * Setup the free lists for stid_tab and atid_tab.
	 */
	if (nstids) {
		while (--nstids)
			t->stid_tab[nstids - 1].next = &t->stid_tab[nstids];
		t->sfree = t->stid_tab;
	}
	if (natids) {
		while (--natids)
			t->atid_tab[natids - 1].next = &t->atid_tab[natids];
		t->afree = t->atid_tab;
	}
	return 0;
}