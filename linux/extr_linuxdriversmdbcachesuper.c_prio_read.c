#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct prio_set {scalar_t__ csum; scalar_t__ magic; struct bucket_disk* data; void* next_bucket; } ;
struct TYPE_2__ {int nbuckets; } ;
struct cache {TYPE_1__ sb; void** prio_last_buckets; void** prio_buckets; struct bucket* buckets; struct prio_set* disk_buckets; } ;
struct bucket_disk {int /*<<< orphan*/  gen; int /*<<< orphan*/  prio; } ;
struct bucket {int /*<<< orphan*/  last_gc; int /*<<< orphan*/  gen; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_READ ; 
 scalar_t__ bch_crc64 (scalar_t__*,scalar_t__) ; 
 scalar_t__ bucket_bytes (struct cache*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  prio_io (struct cache*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int prios_per_bucket (struct cache*) ; 
 scalar_t__ pset_magic (TYPE_1__*) ; 

__attribute__((used)) static void prio_read(struct cache *ca, uint64_t bucket)
{
	struct prio_set *p = ca->disk_buckets;
	struct bucket_disk *d = p->data + prios_per_bucket(ca), *end = d;
	struct bucket *b;
	unsigned int bucket_nr = 0;

	for (b = ca->buckets;
	     b < ca->buckets + ca->sb.nbuckets;
	     b++, d++) {
		if (d == end) {
			ca->prio_buckets[bucket_nr] = bucket;
			ca->prio_last_buckets[bucket_nr] = bucket;
			bucket_nr++;

			prio_io(ca, bucket, REQ_OP_READ, 0);

			if (p->csum !=
			    bch_crc64(&p->magic, bucket_bytes(ca) - 8))
				pr_warn("bad csum reading priorities");

			if (p->magic != pset_magic(&ca->sb))
				pr_warn("bad magic reading priorities");

			bucket = p->next_bucket;
			d = p->data;
		}

		b->prio = le16_to_cpu(d->prio);
		b->gen = b->last_gc = d->gen;
	}
}