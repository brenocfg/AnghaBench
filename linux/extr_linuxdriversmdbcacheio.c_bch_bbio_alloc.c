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
struct cache_set {int /*<<< orphan*/  bio_meta; } ;
struct bio {int /*<<< orphan*/  bi_inline_vecs; } ;
struct bbio {struct bio bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  bio_init (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bucket_pages (struct cache_set*) ; 
 struct bbio* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct bio *bch_bbio_alloc(struct cache_set *c)
{
	struct bbio *b = mempool_alloc(&c->bio_meta, GFP_NOIO);
	struct bio *bio = &b->bio;

	bio_init(bio, bio->bi_inline_vecs, bucket_pages(c));

	return bio;
}