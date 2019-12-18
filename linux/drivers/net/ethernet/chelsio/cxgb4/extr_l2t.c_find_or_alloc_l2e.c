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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct l2t_entry {scalar_t__ state; scalar_t__ vlan; scalar_t__ lport; size_t hash; struct l2t_entry* next; struct l2t_entry* first; int /*<<< orphan*/  dmac; int /*<<< orphan*/  refcnt; } ;
struct l2t_data {size_t l2t_size; struct l2t_entry* l2tab; } ;

/* Variables and functions */
 scalar_t__ L2T_STATE_SWITCHING ; 
 scalar_t__ L2T_STATE_UNUSED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static struct l2t_entry *find_or_alloc_l2e(struct l2t_data *d, u16 vlan,
					   u8 port, u8 *dmac)
{
	struct l2t_entry *end, *e, **p;
	struct l2t_entry *first_free = NULL;

	for (e = &d->l2tab[0], end = &d->l2tab[d->l2t_size]; e != end; ++e) {
		if (atomic_read(&e->refcnt) == 0) {
			if (!first_free)
				first_free = e;
		} else {
			if (e->state == L2T_STATE_SWITCHING) {
				if (ether_addr_equal(e->dmac, dmac) &&
				    (e->vlan == vlan) && (e->lport == port))
					goto exists;
			}
		}
	}

	if (first_free) {
		e = first_free;
		goto found;
	}

	return NULL;

found:
	/* The entry we found may be an inactive entry that is
	 * presently in the hash table.  We need to remove it.
	 */
	if (e->state < L2T_STATE_SWITCHING)
		for (p = &d->l2tab[e->hash].first; *p; p = &(*p)->next)
			if (*p == e) {
				*p = e->next;
				e->next = NULL;
				break;
			}
	e->state = L2T_STATE_UNUSED;

exists:
	return e;
}