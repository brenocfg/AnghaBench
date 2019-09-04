#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct prio_set {long next_bucket; int /*<<< orphan*/  magic; int /*<<< orphan*/  csum; struct bucket_disk* data; int /*<<< orphan*/  seq; } ;
struct closure {int dummy; } ;
struct TYPE_3__ {int bucket_size; int nbuckets; } ;
struct cache {long* prio_buckets; int* prio_last_buckets; struct bucket* buckets; TYPE_2__* set; TYPE_1__ sb; struct prio_set* disk_buckets; int /*<<< orphan*/  meta_sectors_written; } ;
struct bucket_disk {int /*<<< orphan*/  gen; int /*<<< orphan*/  prio; } ;
struct bucket {int /*<<< orphan*/  pin; int /*<<< orphan*/  gen; int /*<<< orphan*/  prio; } ;
struct TYPE_4__ {int /*<<< orphan*/  bucket_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  RESERVE_PRIO ; 
 int /*<<< orphan*/  __bch_bucket_free (struct cache*,struct bucket*) ; 
 int /*<<< orphan*/  atomic_dec_bug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_add (int,int /*<<< orphan*/ *) ; 
 long bch_bucket_alloc (struct cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bch_crc64 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bch_journal_meta (TYPE_2__*,struct closure*) ; 
 scalar_t__ bucket_bytes (struct cache*) ; 
 int /*<<< orphan*/  closure_init_stack (struct closure*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int prio_buckets (struct cache*) ; 
 int /*<<< orphan*/  prio_io (struct cache*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int prios_per_bucket (struct cache*) ; 
 int /*<<< orphan*/  pset_magic (TYPE_1__*) ; 

void bch_prio_write(struct cache *ca)
{
	int i;
	struct bucket *b;
	struct closure cl;

	closure_init_stack(&cl);

	lockdep_assert_held(&ca->set->bucket_lock);

	ca->disk_buckets->seq++;

	atomic_long_add(ca->sb.bucket_size * prio_buckets(ca),
			&ca->meta_sectors_written);

	//pr_debug("free %zu, free_inc %zu, unused %zu", fifo_used(&ca->free),
	//	 fifo_used(&ca->free_inc), fifo_used(&ca->unused));

	for (i = prio_buckets(ca) - 1; i >= 0; --i) {
		long bucket;
		struct prio_set *p = ca->disk_buckets;
		struct bucket_disk *d = p->data;
		struct bucket_disk *end = d + prios_per_bucket(ca);

		for (b = ca->buckets + i * prios_per_bucket(ca);
		     b < ca->buckets + ca->sb.nbuckets && d < end;
		     b++, d++) {
			d->prio = cpu_to_le16(b->prio);
			d->gen = b->gen;
		}

		p->next_bucket	= ca->prio_buckets[i + 1];
		p->magic	= pset_magic(&ca->sb);
		p->csum		= bch_crc64(&p->magic, bucket_bytes(ca) - 8);

		bucket = bch_bucket_alloc(ca, RESERVE_PRIO, true);
		BUG_ON(bucket == -1);

		mutex_unlock(&ca->set->bucket_lock);
		prio_io(ca, bucket, REQ_OP_WRITE, 0);
		mutex_lock(&ca->set->bucket_lock);

		ca->prio_buckets[i] = bucket;
		atomic_dec_bug(&ca->buckets[bucket].pin);
	}

	mutex_unlock(&ca->set->bucket_lock);

	bch_journal_meta(ca->set, &cl);
	closure_sync(&cl);

	mutex_lock(&ca->set->bucket_lock);

	/*
	 * Don't want the old priorities to get garbage collected until after we
	 * finish writing the new ones, and they're journalled
	 */
	for (i = 0; i < prio_buckets(ca); i++) {
		if (ca->prio_last_buckets[i])
			__bch_bucket_free(ca,
				&ca->buckets[ca->prio_last_buckets[i]]);

		ca->prio_last_buckets[i] = ca->prio_buckets[i];
	}
}