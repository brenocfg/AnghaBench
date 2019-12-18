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
typedef  void* u64 ;
struct btt_sb {size_t infooff; scalar_t__ nextoff; scalar_t__ external_nlba; scalar_t__ size; int /*<<< orphan*/  list; void* external_lba_start; } ;
struct btt {size_t rawsize; int num_arenas; int /*<<< orphan*/  init_state; void* nlba; int /*<<< orphan*/  arena_list; int /*<<< orphan*/  nd_btt; } ;
struct arena_info {size_t infooff; scalar_t__ nextoff; scalar_t__ external_nlba; scalar_t__ size; int /*<<< orphan*/  list; void* external_lba_start; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_NOTFOUND ; 
 int /*<<< orphan*/  INIT_READY ; 
 struct btt_sb* alloc_arena (struct btt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btt_freelist_init (struct btt_sb*) ; 
 int btt_info_read (struct btt_sb*,struct btt_sb*) ; 
 int btt_maplocks_init (struct btt_sb*) ; 
 int btt_rtt_init (struct btt_sb*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_arenas (struct btt*) ; 
 int /*<<< orphan*/  kfree (struct btt_sb*) ; 
 struct btt_sb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int log_set_indices (struct btt_sb*) ; 
 int /*<<< orphan*/  nd_btt_arena_is_valid (int /*<<< orphan*/ ,struct btt_sb*) ; 
 int /*<<< orphan*/  parse_arena_meta (struct btt_sb*,struct btt_sb*,size_t) ; 
 int /*<<< orphan*/  to_dev (struct btt_sb*) ; 

__attribute__((used)) static int discover_arenas(struct btt *btt)
{
	int ret = 0;
	struct arena_info *arena;
	struct btt_sb *super;
	size_t remaining = btt->rawsize;
	u64 cur_nlba = 0;
	size_t cur_off = 0;
	int num_arenas = 0;

	super = kzalloc(sizeof(*super), GFP_KERNEL);
	if (!super)
		return -ENOMEM;

	while (remaining) {
		/* Alloc memory for arena */
		arena = alloc_arena(btt, 0, 0, 0);
		if (!arena) {
			ret = -ENOMEM;
			goto out_super;
		}

		arena->infooff = cur_off;
		ret = btt_info_read(arena, super);
		if (ret)
			goto out;

		if (!nd_btt_arena_is_valid(btt->nd_btt, super)) {
			if (remaining == btt->rawsize) {
				btt->init_state = INIT_NOTFOUND;
				dev_info(to_dev(arena), "No existing arenas\n");
				goto out;
			} else {
				dev_err(to_dev(arena),
						"Found corrupted metadata!\n");
				ret = -ENODEV;
				goto out;
			}
		}

		arena->external_lba_start = cur_nlba;
		parse_arena_meta(arena, super, cur_off);

		ret = log_set_indices(arena);
		if (ret) {
			dev_err(to_dev(arena),
				"Unable to deduce log/padding indices\n");
			goto out;
		}

		ret = btt_freelist_init(arena);
		if (ret)
			goto out;

		ret = btt_rtt_init(arena);
		if (ret)
			goto out;

		ret = btt_maplocks_init(arena);
		if (ret)
			goto out;

		list_add_tail(&arena->list, &btt->arena_list);

		remaining -= arena->size;
		cur_off += arena->size;
		cur_nlba += arena->external_nlba;
		num_arenas++;

		if (arena->nextoff == 0)
			break;
	}
	btt->num_arenas = num_arenas;
	btt->nlba = cur_nlba;
	btt->init_state = INIT_READY;

	kfree(super);
	return ret;

 out:
	kfree(arena);
	free_arenas(btt);
 out_super:
	kfree(super);
	return ret;
}