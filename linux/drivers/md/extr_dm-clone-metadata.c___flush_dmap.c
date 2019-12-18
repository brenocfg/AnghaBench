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
struct dm_clone_metadata {unsigned long nr_words; int /*<<< orphan*/  bitmap_lock; } ;
struct dirty_map {scalar_t__ changed; int /*<<< orphan*/  dirty_words; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int __metadata_commit (struct dm_clone_metadata*) ; 
 int __update_metadata_word (struct dm_clone_metadata*,unsigned long) ; 
 unsigned long find_next_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int __flush_dmap(struct dm_clone_metadata *cmd, struct dirty_map *dmap)
{
	int r;
	unsigned long word, flags;

	word = 0;
	do {
		word = find_next_bit(dmap->dirty_words, cmd->nr_words, word);

		if (word == cmd->nr_words)
			break;

		r = __update_metadata_word(cmd, word);

		if (r)
			return r;

		__clear_bit(word, dmap->dirty_words);
		word++;
	} while (word < cmd->nr_words);

	r = __metadata_commit(cmd);

	if (r)
		return r;

	/* Update the changed flag */
	spin_lock_irqsave(&cmd->bitmap_lock, flags);
	dmap->changed = 0;
	spin_unlock_irqrestore(&cmd->bitmap_lock, flags);

	return 0;
}