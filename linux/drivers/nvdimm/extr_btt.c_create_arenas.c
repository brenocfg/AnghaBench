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
struct btt {size_t rawsize; int /*<<< orphan*/  arena_list; int /*<<< orphan*/  nlba; } ;
struct arena_info {int /*<<< orphan*/  list; scalar_t__ nextoff; scalar_t__ size; scalar_t__ external_nlba; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARENA_MAX_SIZE ; 
 size_t ARENA_MIN_SIZE ; 
 int ENOMEM ; 
 struct arena_info* alloc_arena (struct btt*,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  free_arenas (struct btt*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static int create_arenas(struct btt *btt)
{
	size_t remaining = btt->rawsize;
	size_t cur_off = 0;

	while (remaining) {
		struct arena_info *arena;
		size_t arena_size = min_t(u64, ARENA_MAX_SIZE, remaining);

		remaining -= arena_size;
		if (arena_size < ARENA_MIN_SIZE)
			break;

		arena = alloc_arena(btt, arena_size, btt->nlba, cur_off);
		if (!arena) {
			free_arenas(btt);
			return -ENOMEM;
		}
		btt->nlba += arena->external_nlba;
		if (remaining >= ARENA_MIN_SIZE)
			arena->nextoff = arena->size;
		else
			arena->nextoff = 0;
		cur_off += arena_size;
		list_add_tail(&arena->list, &btt->arena_list);
	}

	return 0;
}