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
struct map_info {scalar_t__ virt; } ;
struct async_state {unsigned long win_size; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct async_state* gf_map_info_to_state (struct map_info*) ; 
 int /*<<< orphan*/  gf_set_gpios (struct async_state*,unsigned long) ; 
 int /*<<< orphan*/  memcpy_fromio (void*,scalar_t__,int) ; 

__attribute__((used)) static void gf_copy_from(struct map_info *map, void *to, unsigned long from, ssize_t len)
{
	struct async_state *state = gf_map_info_to_state(map);

	int this_len;

	while (len) {
		if ((from % state->win_size) + len > state->win_size)
			this_len = state->win_size - (from % state->win_size);
		else
			this_len = len;

		gf_set_gpios(state, from);
		memcpy_fromio(to, map->virt + (from % state->win_size),
			 this_len);
		len -= this_len;
		from += this_len;
		to += this_len;
	}
}