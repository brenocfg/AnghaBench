#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct rs_layout {int dummy; } ;
struct raid_type {int dummy; } ;
struct TYPE_15__ {scalar_t__ dev_sectors; int ro; int in_sync; TYPE_2__* pers; int /*<<< orphan*/  recovery; int /*<<< orphan*/  flags; int /*<<< orphan*/  event_work; int /*<<< orphan*/  sync_super; } ;
struct TYPE_13__ {int /*<<< orphan*/  mode; } ;
struct TYPE_12__ {int /*<<< orphan*/  congested_fn; } ;
struct raid_set {TYPE_3__ md; int /*<<< orphan*/  runtime_flags; TYPE_1__ journal_dev; int /*<<< orphan*/  ctr_flags; TYPE_11__ callbacks; } ;
struct dm_target {char* error; int num_flush_bios; int /*<<< orphan*/  table; struct raid_set* private; } ;
struct dm_arg_set {unsigned int member_0; char** member_1; int argc; } ;
struct dm_arg {int member_0; int member_1; char* member_2; int max; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_14__ {int (* check_reshape ) (TYPE_3__*) ;scalar_t__ start_reshape; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct raid_set*) ; 
 int /*<<< orphan*/  MAX_RAID_DEVICES ; 
 int /*<<< orphan*/  MD_ARRAY_FIRST_USE ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 scalar_t__ MaxSector ; 
 int PTR_ERR (struct raid_set*) ; 
 int /*<<< orphan*/  RT_FLAG_RESHAPE_RS ; 
 int /*<<< orphan*/  RT_FLAG_RS_SUSPENDED ; 
 int /*<<< orphan*/  RT_FLAG_UPDATE_SBS ; 
 int /*<<< orphan*/  __CTR_FLAG_JOURNAL_DEV ; 
 int /*<<< orphan*/  __CTR_FLAG_JOURNAL_MODE ; 
 int /*<<< orphan*/  __CTR_FLAG_NOSYNC ; 
 int /*<<< orphan*/  __CTR_FLAG_REBUILD ; 
 int /*<<< orphan*/  __CTR_FLAG_SYNC ; 
 scalar_t__ __rdev_sectors (struct raid_set*) ; 
 int /*<<< orphan*/  __within_range (unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _get_reshape_sectors (struct raid_set*) ; 
 int analyse_superblocks (struct dm_target*,struct raid_set*) ; 
 int /*<<< orphan*/  configure_discard_support (struct raid_set*) ; 
 int /*<<< orphan*/  dm_consume_args (struct dm_arg_set*,unsigned int) ; 
 scalar_t__ dm_read_arg (struct dm_arg*,struct dm_arg_set*,unsigned int*,char**) ; 
 scalar_t__ dm_read_arg_group (struct dm_arg*,struct dm_arg_set*,unsigned int*,char**) ; 
 char* dm_shift_arg (struct dm_arg_set*) ; 
 int /*<<< orphan*/  dm_table_add_target_callbacks (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  do_table_event ; 
 struct raid_type* get_raid_type (char const*) ; 
 int md_run (TYPE_3__*) ; 
 int md_start (TYPE_3__*) ; 
 int /*<<< orphan*/  md_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  mddev_lock_nointr (TYPE_3__*) ; 
 int /*<<< orphan*/  mddev_suspend (TYPE_3__*) ; 
 int /*<<< orphan*/  mddev_unlock (TYPE_3__*) ; 
 int parse_dev_params (struct raid_set*,struct dm_arg_set*) ; 
 int parse_raid_params (struct raid_set*,struct dm_arg_set*,unsigned int) ; 
 int r5c_journal_mode_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid_is_congested ; 
 struct raid_set* raid_set_alloc (struct dm_target*,struct raid_type*,unsigned int) ; 
 int /*<<< orphan*/  raid_set_free (struct raid_set*) ; 
 int rs_adjust_data_offsets (struct raid_set*) ; 
 int rs_check_reshape (struct raid_set*) ; 
 int rs_check_takeover (struct raid_set*) ; 
 int /*<<< orphan*/  rs_config_backup (struct raid_set*,struct rs_layout*) ; 
 int /*<<< orphan*/  rs_config_restore (struct raid_set*,struct rs_layout*) ; 
 scalar_t__ rs_is_raid1 (struct raid_set*) ; 
 scalar_t__ rs_is_raid456 (struct raid_set*) ; 
 scalar_t__ rs_is_raid6 (struct raid_set*) ; 
 scalar_t__ rs_is_recovering (struct raid_set*) ; 
 scalar_t__ rs_is_reshaping (struct raid_set*) ; 
 int rs_prepare_reshape (struct raid_set*) ; 
 scalar_t__ rs_reshape_requested (struct raid_set*) ; 
 int /*<<< orphan*/  rs_set_cur (struct raid_set*) ; 
 int rs_set_dev_and_array_sectors (struct raid_set*,int) ; 
 int /*<<< orphan*/  rs_set_new (struct raid_set*) ; 
 int rs_set_raid456_stripe_cache (struct raid_set*) ; 
 int /*<<< orphan*/  rs_setup_recovery (struct raid_set*,scalar_t__) ; 
 int rs_setup_takeover (struct raid_set*) ; 
 scalar_t__ rs_takeover_requested (struct raid_set*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  super_sync ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	int r;
	bool resize = false;
	struct raid_type *rt;
	unsigned int num_raid_params, num_raid_devs;
	sector_t calculated_dev_sectors, rdev_sectors, reshape_sectors;
	struct raid_set *rs = NULL;
	const char *arg;
	struct rs_layout rs_layout;
	struct dm_arg_set as = { argc, argv }, as_nrd;
	struct dm_arg _args[] = {
		{ 0, as.argc, "Cannot understand number of raid parameters" },
		{ 1, 254, "Cannot understand number of raid devices parameters" }
	};

	/* Must have <raid_type> */
	arg = dm_shift_arg(&as);
	if (!arg) {
		ti->error = "No arguments";
		return -EINVAL;
	}

	rt = get_raid_type(arg);
	if (!rt) {
		ti->error = "Unrecognised raid_type";
		return -EINVAL;
	}

	/* Must have <#raid_params> */
	if (dm_read_arg_group(_args, &as, &num_raid_params, &ti->error))
		return -EINVAL;

	/* number of raid device tupples <meta_dev data_dev> */
	as_nrd = as;
	dm_consume_args(&as_nrd, num_raid_params);
	_args[1].max = (as_nrd.argc - 1) / 2;
	if (dm_read_arg(_args + 1, &as_nrd, &num_raid_devs, &ti->error))
		return -EINVAL;

	if (!__within_range(num_raid_devs, 1, MAX_RAID_DEVICES)) {
		ti->error = "Invalid number of supplied raid devices";
		return -EINVAL;
	}

	rs = raid_set_alloc(ti, rt, num_raid_devs);
	if (IS_ERR(rs))
		return PTR_ERR(rs);

	r = parse_raid_params(rs, &as, num_raid_params);
	if (r)
		goto bad;

	r = parse_dev_params(rs, &as);
	if (r)
		goto bad;

	rs->md.sync_super = super_sync;

	/*
	 * Calculate ctr requested array and device sizes to allow
	 * for superblock analysis needing device sizes defined.
	 *
	 * Any existing superblock will overwrite the array and device sizes
	 */
	r = rs_set_dev_and_array_sectors(rs, false);
	if (r)
		goto bad;

	calculated_dev_sectors = rs->md.dev_sectors;

	/*
	 * Backup any new raid set level, layout, ...
	 * requested to be able to compare to superblock
	 * members for conversion decisions.
	 */
	rs_config_backup(rs, &rs_layout);

	r = analyse_superblocks(ti, rs);
	if (r)
		goto bad;

	rdev_sectors = __rdev_sectors(rs);
	if (!rdev_sectors) {
		ti->error = "Invalid rdev size";
		r = -EINVAL;
		goto bad;
	}


	reshape_sectors = _get_reshape_sectors(rs);
	if (calculated_dev_sectors != rdev_sectors)
		resize = calculated_dev_sectors != (reshape_sectors ? rdev_sectors - reshape_sectors : rdev_sectors);

	INIT_WORK(&rs->md.event_work, do_table_event);
	ti->private = rs;
	ti->num_flush_bios = 1;

	/* Restore any requested new layout for conversion decision */
	rs_config_restore(rs, &rs_layout);

	/*
	 * Now that we have any superblock metadata available,
	 * check for new, recovering, reshaping, to be taken over,
	 * to be reshaped or an existing, unchanged raid set to
	 * run in sequence.
	 */
	if (test_bit(MD_ARRAY_FIRST_USE, &rs->md.flags)) {
		/* A new raid6 set has to be recovered to ensure proper parity and Q-Syndrome */
		if (rs_is_raid6(rs) &&
		    test_bit(__CTR_FLAG_NOSYNC, &rs->ctr_flags)) {
			ti->error = "'nosync' not allowed for new raid6 set";
			r = -EINVAL;
			goto bad;
		}
		rs_setup_recovery(rs, 0);
		set_bit(RT_FLAG_UPDATE_SBS, &rs->runtime_flags);
		rs_set_new(rs);
	} else if (rs_is_recovering(rs)) {
		/* Rebuild particular devices */
		if (test_bit(__CTR_FLAG_REBUILD, &rs->ctr_flags)) {
			set_bit(RT_FLAG_UPDATE_SBS, &rs->runtime_flags);
			rs_setup_recovery(rs, MaxSector);
		}
		/* A recovering raid set may be resized */
		; /* skip setup rs */
	} else if (rs_is_reshaping(rs)) {
		/* Have to reject size change request during reshape */
		if (resize) {
			ti->error = "Can't resize a reshaping raid set";
			r = -EPERM;
			goto bad;
		}
		/* skip setup rs */
	} else if (rs_takeover_requested(rs)) {
		if (rs_is_reshaping(rs)) {
			ti->error = "Can't takeover a reshaping raid set";
			r = -EPERM;
			goto bad;
		}

		/* We can't takeover a journaled raid4/5/6 */
		if (test_bit(__CTR_FLAG_JOURNAL_DEV, &rs->ctr_flags)) {
			ti->error = "Can't takeover a journaled raid4/5/6 set";
			r = -EPERM;
			goto bad;
		}

		/*
		 * If a takeover is needed, userspace sets any additional
		 * devices to rebuild and we can check for a valid request here.
		 *
		 * If acceptible, set the level to the new requested
		 * one, prohibit requesting recovery, allow the raid
		 * set to run and store superblocks during resume.
		 */
		r = rs_check_takeover(rs);
		if (r)
			goto bad;

		r = rs_setup_takeover(rs);
		if (r)
			goto bad;

		set_bit(RT_FLAG_UPDATE_SBS, &rs->runtime_flags);
		/* Takeover ain't recovery, so disable recovery */
		rs_setup_recovery(rs, MaxSector);
		rs_set_new(rs);
	} else if (rs_reshape_requested(rs)) {
		/*
		 * No need to check for 'ongoing' takeover here, because takeover
		 * is an instant operation as oposed to an ongoing reshape.
		 */

		/* We can't reshape a journaled raid4/5/6 */
		if (test_bit(__CTR_FLAG_JOURNAL_DEV, &rs->ctr_flags)) {
			ti->error = "Can't reshape a journaled raid4/5/6 set";
			r = -EPERM;
			goto bad;
		}

		/* Out-of-place space has to be available to allow for a reshape unless raid1! */
		if (reshape_sectors || rs_is_raid1(rs)) {
			/*
			  * We can only prepare for a reshape here, because the
			  * raid set needs to run to provide the repective reshape
			  * check functions via its MD personality instance.
			  *
			  * So do the reshape check after md_run() succeeded.
			  */
			r = rs_prepare_reshape(rs);
			if (r)
				goto bad;

			/* Reshaping ain't recovery, so disable recovery */
			rs_setup_recovery(rs, MaxSector);
		}
		rs_set_cur(rs);
	} else {
		/* May not set recovery when a device rebuild is requested */
		if (test_bit(__CTR_FLAG_REBUILD, &rs->ctr_flags)) {
			rs_setup_recovery(rs, MaxSector);
			set_bit(RT_FLAG_UPDATE_SBS, &rs->runtime_flags);
		} else
			rs_setup_recovery(rs, test_bit(__CTR_FLAG_SYNC, &rs->ctr_flags) ?
					      0 : (resize ? calculated_dev_sectors : MaxSector));
		rs_set_cur(rs);
	}

	/* If constructor requested it, change data and new_data offsets */
	r = rs_adjust_data_offsets(rs);
	if (r)
		goto bad;

	/* Start raid set read-only and assumed clean to change in raid_resume() */
	rs->md.ro = 1;
	rs->md.in_sync = 1;

	/* Keep array frozen */
	set_bit(MD_RECOVERY_FROZEN, &rs->md.recovery);

	/* Has to be held on running the array */
	mddev_lock_nointr(&rs->md);
	r = md_run(&rs->md);
	rs->md.in_sync = 0; /* Assume already marked dirty */
	if (r) {
		ti->error = "Failed to run raid array";
		mddev_unlock(&rs->md);
		goto bad;
	}

	r = md_start(&rs->md);

	if (r) {
		ti->error = "Failed to start raid array";
		mddev_unlock(&rs->md);
		goto bad_md_start;
	}

	rs->callbacks.congested_fn = raid_is_congested;
	dm_table_add_target_callbacks(ti->table, &rs->callbacks);

	/* If raid4/5/6 journal mode explicitly requested (only possible with journal dev) -> set it */
	if (test_bit(__CTR_FLAG_JOURNAL_MODE, &rs->ctr_flags)) {
		r = r5c_journal_mode_set(&rs->md, rs->journal_dev.mode);
		if (r) {
			ti->error = "Failed to set raid4/5/6 journal mode";
			mddev_unlock(&rs->md);
			goto bad_journal_mode_set;
		}
	}

	mddev_suspend(&rs->md);
	set_bit(RT_FLAG_RS_SUSPENDED, &rs->runtime_flags);

	/* Try to adjust the raid4/5/6 stripe cache size to the stripe size */
	if (rs_is_raid456(rs)) {
		r = rs_set_raid456_stripe_cache(rs);
		if (r)
			goto bad_stripe_cache;
	}

	/* Now do an early reshape check */
	if (test_bit(RT_FLAG_RESHAPE_RS, &rs->runtime_flags)) {
		r = rs_check_reshape(rs);
		if (r)
			goto bad_check_reshape;

		/* Restore new, ctr requested layout to perform check */
		rs_config_restore(rs, &rs_layout);

		if (rs->md.pers->start_reshape) {
			r = rs->md.pers->check_reshape(&rs->md);
			if (r) {
				ti->error = "Reshape check failed";
				goto bad_check_reshape;
			}
		}
	}

	/* Disable/enable discard support on raid set. */
	configure_discard_support(rs);

	mddev_unlock(&rs->md);
	return 0;

bad_md_start:
bad_journal_mode_set:
bad_stripe_cache:
bad_check_reshape:
	md_stop(&rs->md);
bad:
	raid_set_free(rs);

	return r;
}