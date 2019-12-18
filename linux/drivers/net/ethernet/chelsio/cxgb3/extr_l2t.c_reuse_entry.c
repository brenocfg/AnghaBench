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
struct neighbour {unsigned int nud_state; int /*<<< orphan*/  ha; } ;
struct l2t_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  dmac; struct neighbour* neigh; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2T_STATE_RESOLVING ; 
 int /*<<< orphan*/  L2T_STATE_STALE ; 
 int /*<<< orphan*/  L2T_STATE_VALID ; 
 unsigned int NUD_CONNECTED ; 
 unsigned int NUD_VALID ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neigh_replace (struct l2t_entry*,struct neighbour*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void reuse_entry(struct l2t_entry *e, struct neighbour *neigh)
{
	unsigned int nud_state;

	spin_lock(&e->lock);	/* avoid race with t3_l2t_free */

	if (neigh != e->neigh)
		neigh_replace(e, neigh);
	nud_state = neigh->nud_state;
	if (memcmp(e->dmac, neigh->ha, sizeof(e->dmac)) ||
	    !(nud_state & NUD_VALID))
		e->state = L2T_STATE_RESOLVING;
	else if (nud_state & NUD_CONNECTED)
		e->state = L2T_STATE_VALID;
	else
		e->state = L2T_STATE_STALE;
	spin_unlock(&e->lock);
}