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
struct fwnet_peer {int /*<<< orphan*/  pd_list; } ;
struct fwnet_partial_datagram {unsigned int pbuf; int /*<<< orphan*/  pd_link; } ;

/* Variables and functions */
 int /*<<< orphan*/ * fwnet_frag_new (struct fwnet_partial_datagram*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned int,void*,unsigned int) ; 

__attribute__((used)) static bool fwnet_pd_update(struct fwnet_peer *peer,
		struct fwnet_partial_datagram *pd, void *frag_buf,
		unsigned frag_off, unsigned frag_len)
{
	if (fwnet_frag_new(pd, frag_off, frag_len) == NULL)
		return false;

	memcpy(pd->pbuf + frag_off, frag_buf, frag_len);

	/*
	 * Move list entry to beginning of list so that oldest partial
	 * datagrams percolate to the end of the list
	 */
	list_move_tail(&pd->pd_link, &peer->pd_list);

	return true;
}