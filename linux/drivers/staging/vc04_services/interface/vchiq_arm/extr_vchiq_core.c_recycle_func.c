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
struct vchiq_state {int /*<<< orphan*/  recycle_event; struct vchiq_shared_state* local; } ;
struct vchiq_shared_state {int /*<<< orphan*/  recycle; } ;
typedef  int /*<<< orphan*/  BITSET_T ;

/* Variables and functions */
 int BITSET_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VCHIQ_MAX_SERVICES ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_free_queue (struct vchiq_state*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  remote_event_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
recycle_func(void *v)
{
	struct vchiq_state *state = v;
	struct vchiq_shared_state *local = state->local;
	BITSET_T *found;
	size_t length;

	length = sizeof(*found) * BITSET_SIZE(VCHIQ_MAX_SERVICES);

	found = kmalloc_array(BITSET_SIZE(VCHIQ_MAX_SERVICES), sizeof(*found),
			      GFP_KERNEL);
	if (!found)
		return -ENOMEM;

	while (1) {
		remote_event_wait(&state->recycle_event, &local->recycle);

		process_free_queue(state, found, length);
	}
	return 0;
}