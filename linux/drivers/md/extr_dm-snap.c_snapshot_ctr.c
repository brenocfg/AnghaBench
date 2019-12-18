#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dm_target {char* error; unsigned int num_flush_bios; int num_discard_bios; int per_io_data_size; struct dm_snapshot* private; int /*<<< orphan*/  table; } ;
struct dm_snapshot {int valid; TYPE_4__* origin; TYPE_4__* cow; TYPE_3__* store; int /*<<< orphan*/  complete; int /*<<< orphan*/  pending; int /*<<< orphan*/  kcopyd_client; int /*<<< orphan*/  pending_pool; scalar_t__ discard_passdown_origin; scalar_t__ discard_zeroes_cow; int /*<<< orphan*/  tracked_chunk_lock; int /*<<< orphan*/ * tracked_chunk_hash; int /*<<< orphan*/  in_progress_wait; int /*<<< orphan*/  bios_queued_during_merge; scalar_t__ num_merging_chunks; scalar_t__ first_merging_chunk; scalar_t__ merge_failed; scalar_t__ state_bits; int /*<<< orphan*/  pe_lock; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; int /*<<< orphan*/  out_of_order_tree; scalar_t__ exception_complete_sequence; scalar_t__ exception_start_sequence; int /*<<< orphan*/  pe_allocation_lock; int /*<<< orphan*/  pending_exceptions_count; scalar_t__ active; scalar_t__ snapshot_overflowed; struct dm_target* ti; } ;
struct dm_snap_tracked_chunk {int dummy; } ;
struct dm_arg_set {unsigned int argc; char** argv; } ;
typedef  int /*<<< orphan*/  fmode_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_11__ {TYPE_2__* bdev; } ;
struct TYPE_10__ {scalar_t__ chunk_size; TYPE_1__* type; } ;
struct TYPE_9__ {scalar_t__ bd_dev; } ;
struct TYPE_8__ {int (* read_metadata ) (TYPE_3__*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int DM_TRACKED_CHUNK_HASH_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_IOS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_add_exception ; 
 int /*<<< orphan*/  dm_consume_args (struct dm_arg_set*,int) ; 
 int dm_exception_store_create (struct dm_target*,unsigned int,char**,struct dm_snapshot*,unsigned int*,TYPE_3__**) ; 
 int /*<<< orphan*/  dm_exception_store_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  dm_exception_table_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dm_get_dev_t (char*) ; 
 int dm_get_device (struct dm_target*,char*,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  dm_kcopyd_client_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_kcopyd_client_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_kcopyd_throttle ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,TYPE_4__*) ; 
 int dm_set_target_max_io_len (struct dm_target*,scalar_t__) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ dm_target_is_snapshot_merge (struct dm_target*) ; 
 int /*<<< orphan*/  exception_cache ; 
 scalar_t__ init_hash_tables (struct dm_snapshot*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_snapshot*) ; 
 struct dm_snapshot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int mempool_init_slab_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_snapshot_features (struct dm_arg_set*,struct dm_snapshot*,struct dm_target*) ; 
 int /*<<< orphan*/  pending_cache ; 
 int register_snapshot (struct dm_snapshot*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  unregister_snapshot (struct dm_snapshot*) ; 

__attribute__((used)) static int snapshot_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	struct dm_snapshot *s;
	struct dm_arg_set as;
	int i;
	int r = -EINVAL;
	char *origin_path, *cow_path;
	dev_t origin_dev, cow_dev;
	unsigned args_used, num_flush_bios = 1;
	fmode_t origin_mode = FMODE_READ;

	if (argc < 4) {
		ti->error = "requires 4 or more arguments";
		r = -EINVAL;
		goto bad;
	}

	if (dm_target_is_snapshot_merge(ti)) {
		num_flush_bios = 2;
		origin_mode = FMODE_WRITE;
	}

	s = kzalloc(sizeof(*s), GFP_KERNEL);
	if (!s) {
		ti->error = "Cannot allocate private snapshot structure";
		r = -ENOMEM;
		goto bad;
	}

	as.argc = argc;
	as.argv = argv;
	dm_consume_args(&as, 4);
	r = parse_snapshot_features(&as, s, ti);
	if (r)
		goto bad_features;

	origin_path = argv[0];
	argv++;
	argc--;

	r = dm_get_device(ti, origin_path, origin_mode, &s->origin);
	if (r) {
		ti->error = "Cannot get origin device";
		goto bad_origin;
	}
	origin_dev = s->origin->bdev->bd_dev;

	cow_path = argv[0];
	argv++;
	argc--;

	cow_dev = dm_get_dev_t(cow_path);
	if (cow_dev && cow_dev == origin_dev) {
		ti->error = "COW device cannot be the same as origin device";
		r = -EINVAL;
		goto bad_cow;
	}

	r = dm_get_device(ti, cow_path, dm_table_get_mode(ti->table), &s->cow);
	if (r) {
		ti->error = "Cannot get COW device";
		goto bad_cow;
	}

	r = dm_exception_store_create(ti, argc, argv, s, &args_used, &s->store);
	if (r) {
		ti->error = "Couldn't create exception store";
		r = -EINVAL;
		goto bad_store;
	}

	argv += args_used;
	argc -= args_used;

	s->ti = ti;
	s->valid = 1;
	s->snapshot_overflowed = 0;
	s->active = 0;
	atomic_set(&s->pending_exceptions_count, 0);
	spin_lock_init(&s->pe_allocation_lock);
	s->exception_start_sequence = 0;
	s->exception_complete_sequence = 0;
	s->out_of_order_tree = RB_ROOT;
	init_rwsem(&s->lock);
	INIT_LIST_HEAD(&s->list);
	spin_lock_init(&s->pe_lock);
	s->state_bits = 0;
	s->merge_failed = 0;
	s->first_merging_chunk = 0;
	s->num_merging_chunks = 0;
	bio_list_init(&s->bios_queued_during_merge);

	/* Allocate hash table for COW data */
	if (init_hash_tables(s)) {
		ti->error = "Unable to allocate hash table space";
		r = -ENOMEM;
		goto bad_hash_tables;
	}

	init_waitqueue_head(&s->in_progress_wait);

	s->kcopyd_client = dm_kcopyd_client_create(&dm_kcopyd_throttle);
	if (IS_ERR(s->kcopyd_client)) {
		r = PTR_ERR(s->kcopyd_client);
		ti->error = "Could not create kcopyd client";
		goto bad_kcopyd;
	}

	r = mempool_init_slab_pool(&s->pending_pool, MIN_IOS, pending_cache);
	if (r) {
		ti->error = "Could not allocate mempool for pending exceptions";
		goto bad_pending_pool;
	}

	for (i = 0; i < DM_TRACKED_CHUNK_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&s->tracked_chunk_hash[i]);

	spin_lock_init(&s->tracked_chunk_lock);

	ti->private = s;
	ti->num_flush_bios = num_flush_bios;
	if (s->discard_zeroes_cow)
		ti->num_discard_bios = (s->discard_passdown_origin ? 2 : 1);
	ti->per_io_data_size = sizeof(struct dm_snap_tracked_chunk);

	/* Add snapshot to the list of snapshots for this origin */
	/* Exceptions aren't triggered till snapshot_resume() is called */
	r = register_snapshot(s);
	if (r == -ENOMEM) {
		ti->error = "Snapshot origin struct allocation failed";
		goto bad_load_and_register;
	} else if (r < 0) {
		/* invalid handover, register_snapshot has set ti->error */
		goto bad_load_and_register;
	}

	/*
	 * Metadata must only be loaded into one table at once, so skip this
	 * if metadata will be handed over during resume.
	 * Chunk size will be set during the handover - set it to zero to
	 * ensure it's ignored.
	 */
	if (r > 0) {
		s->store->chunk_size = 0;
		return 0;
	}

	r = s->store->type->read_metadata(s->store, dm_add_exception,
					  (void *)s);
	if (r < 0) {
		ti->error = "Failed to read snapshot metadata";
		goto bad_read_metadata;
	} else if (r > 0) {
		s->valid = 0;
		DMWARN("Snapshot is marked invalid.");
	}

	if (!s->store->chunk_size) {
		ti->error = "Chunk size not set";
		goto bad_read_metadata;
	}

	r = dm_set_target_max_io_len(ti, s->store->chunk_size);
	if (r)
		goto bad_read_metadata;

	return 0;

bad_read_metadata:
	unregister_snapshot(s);
bad_load_and_register:
	mempool_exit(&s->pending_pool);
bad_pending_pool:
	dm_kcopyd_client_destroy(s->kcopyd_client);
bad_kcopyd:
	dm_exception_table_exit(&s->pending, pending_cache);
	dm_exception_table_exit(&s->complete, exception_cache);
bad_hash_tables:
	dm_exception_store_destroy(s->store);
bad_store:
	dm_put_device(ti, s->cow);
bad_cow:
	dm_put_device(ti, s->origin);
bad_origin:
bad_features:
	kfree(s);
bad:
	return r;
}