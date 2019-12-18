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
struct rdma_dev_addr {int /*<<< orphan*/  dst_dev_addr; } ;
struct neighbour {int nud_state; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODATA ; 
 int NUD_VALID ; 
 struct neighbour* dst_neigh_lookup (struct dst_entry const*,void const*) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_ha_snapshot (int /*<<< orphan*/ ,struct neighbour*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 

__attribute__((used)) static int dst_fetch_ha(const struct dst_entry *dst,
			struct rdma_dev_addr *dev_addr,
			const void *daddr)
{
	struct neighbour *n;
	int ret = 0;

	n = dst_neigh_lookup(dst, daddr);
	if (!n)
		return -ENODATA;

	if (!(n->nud_state & NUD_VALID)) {
		neigh_event_send(n, NULL);
		ret = -ENODATA;
	} else {
		neigh_ha_snapshot(dev_addr->dst_dev_addr, n, dst->dev);
	}

	neigh_release(n);

	return ret;
}