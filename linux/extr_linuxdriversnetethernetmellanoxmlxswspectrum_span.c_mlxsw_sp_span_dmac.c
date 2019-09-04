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
struct net_device {int dummy; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  ha; int /*<<< orphan*/  dead; } ;
struct neigh_table {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 int NUD_VALID ; 
 int PTR_ERR (struct neighbour*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct neighbour* neigh_create (struct neigh_table*,void const*,struct net_device*) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 struct neighbour* neigh_lookup (struct neigh_table*,void const*,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_span_dmac(struct neigh_table *tbl,
			      const void *pkey,
			      struct net_device *dev,
			      unsigned char dmac[ETH_ALEN])
{
	struct neighbour *neigh = neigh_lookup(tbl, pkey, dev);
	int err = 0;

	if (!neigh) {
		neigh = neigh_create(tbl, pkey, dev);
		if (IS_ERR(neigh))
			return PTR_ERR(neigh);
	}

	neigh_event_send(neigh, NULL);

	read_lock_bh(&neigh->lock);
	if ((neigh->nud_state & NUD_VALID) && !neigh->dead)
		memcpy(dmac, neigh->ha, ETH_ALEN);
	else
		err = -ENOENT;
	read_unlock_bh(&neigh->lock);

	neigh_release(neigh);
	return err;
}