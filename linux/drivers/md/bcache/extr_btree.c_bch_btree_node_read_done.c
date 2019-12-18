#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct btree_iter {int size; TYPE_2__* b; scalar_t__ used; } ;
struct TYPE_10__ {TYPE_1__* set; } ;
struct btree {scalar_t__ written; int /*<<< orphan*/  key; TYPE_4__* c; TYPE_2__ keys; } ;
struct bset {scalar_t__ seq; int version; scalar_t__ magic; int /*<<< orphan*/  keys; int /*<<< orphan*/  start; int /*<<< orphan*/  csum; } ;
struct TYPE_11__ {int bucket_size; int block_size; } ;
struct TYPE_12__ {int /*<<< orphan*/  fill_iter; TYPE_3__ sb; int /*<<< orphan*/  sort; } ;
struct TYPE_9__ {int /*<<< orphan*/  end; scalar_t__ size; struct bset* data; } ;

/* Variables and functions */
#define  BCACHE_BSET_VERSION 128 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ KEY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_BUCKET_NR (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_bset_init_next (TYPE_2__*,struct bset*,scalar_t__) ; 
 int /*<<< orphan*/  bch_btree_iter_push (struct btree_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_btree_sort_and_fix_extents (TYPE_2__*,struct btree_iter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_cache_set_error (TYPE_4__*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bkey_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int block_bytes (TYPE_4__*) ; 
 int /*<<< orphan*/  bset_bkey_last (struct bset*) ; 
 int /*<<< orphan*/  bset_block_offset (struct btree*,struct bset*) ; 
 scalar_t__ bset_magic (TYPE_3__*) ; 
 scalar_t__ bset_sector_offset (TYPE_2__*,struct bset*) ; 
 scalar_t__ btree_blocks (struct btree*) ; 
 struct bset* btree_bset_first (struct btree*) ; 
 int /*<<< orphan*/  btree_csum_set (struct btree*,struct bset*) ; 
 int /*<<< orphan*/  csum_set (struct bset*) ; 
 struct btree_iter* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct btree_iter*,int /*<<< orphan*/ *) ; 
 scalar_t__ set_blocks (struct bset*,int) ; 
 int /*<<< orphan*/  set_btree_node_io_error (struct btree*) ; 
 struct bset* write_block (struct btree*) ; 

void bch_btree_node_read_done(struct btree *b)
{
	const char *err = "bad btree header";
	struct bset *i = btree_bset_first(b);
	struct btree_iter *iter;

	/*
	 * c->fill_iter can allocate an iterator with more memory space
	 * than static MAX_BSETS.
	 * See the comment arount cache_set->fill_iter.
	 */
	iter = mempool_alloc(&b->c->fill_iter, GFP_NOIO);
	iter->size = b->c->sb.bucket_size / b->c->sb.block_size;
	iter->used = 0;

#ifdef CONFIG_BCACHE_DEBUG
	iter->b = &b->keys;
#endif

	if (!i->seq)
		goto err;

	for (;
	     b->written < btree_blocks(b) && i->seq == b->keys.set[0].data->seq;
	     i = write_block(b)) {
		err = "unsupported bset version";
		if (i->version > BCACHE_BSET_VERSION)
			goto err;

		err = "bad btree header";
		if (b->written + set_blocks(i, block_bytes(b->c)) >
		    btree_blocks(b))
			goto err;

		err = "bad magic";
		if (i->magic != bset_magic(&b->c->sb))
			goto err;

		err = "bad checksum";
		switch (i->version) {
		case 0:
			if (i->csum != csum_set(i))
				goto err;
			break;
		case BCACHE_BSET_VERSION:
			if (i->csum != btree_csum_set(b, i))
				goto err;
			break;
		}

		err = "empty set";
		if (i != b->keys.set[0].data && !i->keys)
			goto err;

		bch_btree_iter_push(iter, i->start, bset_bkey_last(i));

		b->written += set_blocks(i, block_bytes(b->c));
	}

	err = "corrupted btree";
	for (i = write_block(b);
	     bset_sector_offset(&b->keys, i) < KEY_SIZE(&b->key);
	     i = ((void *) i) + block_bytes(b->c))
		if (i->seq == b->keys.set[0].data->seq)
			goto err;

	bch_btree_sort_and_fix_extents(&b->keys, iter, &b->c->sort);

	i = b->keys.set[0].data;
	err = "short btree key";
	if (b->keys.set[0].size &&
	    bkey_cmp(&b->key, &b->keys.set[0].end) < 0)
		goto err;

	if (b->written < btree_blocks(b))
		bch_bset_init_next(&b->keys, write_block(b),
				   bset_magic(&b->c->sb));
out:
	mempool_free(iter, &b->c->fill_iter);
	return;
err:
	set_btree_node_io_error(b);
	bch_cache_set_error(b->c, "%s at bucket %zu, block %u, %u keys",
			    err, PTR_BUCKET_NR(b->c, &b->key, 0),
			    bset_block_offset(b, i), i->keys);
	goto out;
}