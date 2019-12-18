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
struct ctlr_info {scalar_t__ cmd_pool_bits; struct CommandList* cmd_pool; } ;
struct CommandList {int /*<<< orphan*/ * device; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int HPSA_NRESERVED_CMDS ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmd_free (struct ctlr_info*,struct CommandList*) ; 
 int find_next_zero_bit (scalar_t__,int,int) ; 
 int /*<<< orphan*/  hpsa_cmd_partial_init (struct ctlr_info*,int,struct CommandList*) ; 
 int /*<<< orphan*/  set_bit (int,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct CommandList *cmd_alloc(struct ctlr_info *h)
{
	struct CommandList *c;
	int refcount, i;
	int offset = 0;

	/*
	 * There is some *extremely* small but non-zero chance that that
	 * multiple threads could get in here, and one thread could
	 * be scanning through the list of bits looking for a free
	 * one, but the free ones are always behind him, and other
	 * threads sneak in behind him and eat them before he can
	 * get to them, so that while there is always a free one, a
	 * very unlucky thread might be starved anyway, never able to
	 * beat the other threads.  In reality, this happens so
	 * infrequently as to be indistinguishable from never.
	 *
	 * Note that we start allocating commands before the SCSI host structure
	 * is initialized.  Since the search starts at bit zero, this
	 * all works, since we have at least one command structure available;
	 * however, it means that the structures with the low indexes have to be
	 * reserved for driver-initiated requests, while requests from the block
	 * layer will use the higher indexes.
	 */

	for (;;) {
		i = find_next_zero_bit(h->cmd_pool_bits,
					HPSA_NRESERVED_CMDS,
					offset);
		if (unlikely(i >= HPSA_NRESERVED_CMDS)) {
			offset = 0;
			continue;
		}
		c = h->cmd_pool + i;
		refcount = atomic_inc_return(&c->refcount);
		if (unlikely(refcount > 1)) {
			cmd_free(h, c); /* already in use */
			offset = (i + 1) % HPSA_NRESERVED_CMDS;
			continue;
		}
		set_bit(i & (BITS_PER_LONG - 1),
			h->cmd_pool_bits + (i / BITS_PER_LONG));
		break; /* it's ours now. */
	}
	hpsa_cmd_partial_init(h, i, c);
	c->device = NULL;
	return c;
}