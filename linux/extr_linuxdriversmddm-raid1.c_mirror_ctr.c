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
struct mirror_set {unsigned int nr_mirrors; int /*<<< orphan*/  kmirrord_wq; int /*<<< orphan*/  kcopyd_client; int /*<<< orphan*/  trigger_event; scalar_t__ timer_pending; int /*<<< orphan*/  timer; int /*<<< orphan*/  kmirrord_work; int /*<<< orphan*/  rh; } ;
struct dm_target {char* error; int num_flush_bios; int num_discard_bios; int per_io_data_size; struct mirror_set* private; } ;
struct dm_raid1_bio_record {int dummy; } ;
struct dm_dirty_log {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_region_size ) (struct dm_dirty_log*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned int MAX_NR_MIRRORS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 struct mirror_set* alloc_context (unsigned int,int /*<<< orphan*/ ,struct dm_target*,struct dm_dirty_log*) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dm_dirty_log* create_dirty_log (struct dm_target*,unsigned int,char**,unsigned int*) ; 
 int /*<<< orphan*/  delayed_wake_fn ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_dirty_log_destroy (struct dm_dirty_log*) ; 
 int /*<<< orphan*/  dm_kcopyd_client_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_kcopyd_throttle ; 
 int /*<<< orphan*/  dm_rh_get_region_size (int /*<<< orphan*/ ) ; 
 int dm_set_target_max_io_len (struct dm_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_mirror ; 
 int /*<<< orphan*/  free_context (struct mirror_set*,struct dm_target*,unsigned int) ; 
 int get_mirror (struct mirror_set*,struct dm_target*,unsigned int,char**) ; 
 int parse_features (struct mirror_set*,unsigned int,char**,unsigned int*) ; 
 int sscanf (char*,char*,unsigned int*,char*) ; 
 int /*<<< orphan*/  stub1 (struct dm_dirty_log*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trigger_event ; 
 int /*<<< orphan*/  wakeup_mirrord (struct mirror_set*) ; 

__attribute__((used)) static int mirror_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	int r;
	unsigned int nr_mirrors, m, args_used;
	struct mirror_set *ms;
	struct dm_dirty_log *dl;
	char dummy;

	dl = create_dirty_log(ti, argc, argv, &args_used);
	if (!dl)
		return -EINVAL;

	argv += args_used;
	argc -= args_used;

	if (!argc || sscanf(argv[0], "%u%c", &nr_mirrors, &dummy) != 1 ||
	    nr_mirrors < 2 || nr_mirrors > MAX_NR_MIRRORS) {
		ti->error = "Invalid number of mirrors";
		dm_dirty_log_destroy(dl);
		return -EINVAL;
	}

	argv++, argc--;

	if (argc < nr_mirrors * 2) {
		ti->error = "Too few mirror arguments";
		dm_dirty_log_destroy(dl);
		return -EINVAL;
	}

	ms = alloc_context(nr_mirrors, dl->type->get_region_size(dl), ti, dl);
	if (!ms) {
		dm_dirty_log_destroy(dl);
		return -ENOMEM;
	}

	/* Get the mirror parameter sets */
	for (m = 0; m < nr_mirrors; m++) {
		r = get_mirror(ms, ti, m, argv);
		if (r) {
			free_context(ms, ti, m);
			return r;
		}
		argv += 2;
		argc -= 2;
	}

	ti->private = ms;

	r = dm_set_target_max_io_len(ti, dm_rh_get_region_size(ms->rh));
	if (r)
		goto err_free_context;

	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->per_io_data_size = sizeof(struct dm_raid1_bio_record);

	ms->kmirrord_wq = alloc_workqueue("kmirrord", WQ_MEM_RECLAIM, 0);
	if (!ms->kmirrord_wq) {
		DMERR("couldn't start kmirrord");
		r = -ENOMEM;
		goto err_free_context;
	}
	INIT_WORK(&ms->kmirrord_work, do_mirror);
	timer_setup(&ms->timer, delayed_wake_fn, 0);
	ms->timer_pending = 0;
	INIT_WORK(&ms->trigger_event, trigger_event);

	r = parse_features(ms, argc, argv, &args_used);
	if (r)
		goto err_destroy_wq;

	argv += args_used;
	argc -= args_used;

	/*
	 * Any read-balancing addition depends on the
	 * DM_RAID1_HANDLE_ERRORS flag being present.
	 * This is because the decision to balance depends
	 * on the sync state of a region.  If the above
	 * flag is not present, we ignore errors; and
	 * the sync state may be inaccurate.
	 */

	if (argc) {
		ti->error = "Too many mirror arguments";
		r = -EINVAL;
		goto err_destroy_wq;
	}

	ms->kcopyd_client = dm_kcopyd_client_create(&dm_kcopyd_throttle);
	if (IS_ERR(ms->kcopyd_client)) {
		r = PTR_ERR(ms->kcopyd_client);
		goto err_destroy_wq;
	}

	wakeup_mirrord(ms);
	return 0;

err_destroy_wq:
	destroy_workqueue(ms->kmirrord_wq);
err_free_context:
	free_context(ms, ti, ms->nr_mirrors);
	return r;
}