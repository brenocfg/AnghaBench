#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  groups; int /*<<< orphan*/ * class; int /*<<< orphan*/  release; } ;
struct TYPE_6__ {int max_size; scalar_t__ size; scalar_t__ used; } ;
struct TYPE_5__ {int max_size; scalar_t__ size; scalar_t__ used; } ;
struct ubi_device {int ubi_num; int vid_hdr_offset; int autoresize_vol_id; int fm_disabled; int peb_size; int bgt_name; int flash_size; int leb_size; int min_io_size; int max_write_size; int hdrs_min_io_size; int vid_hdr_aloffset; int leb_start; int good_peb_count; int bad_peb_count; int corr_peb_count; int vol_count; int vtbl_slots; int avail_pebs; int rsvd_pebs; int beb_rsvd_pebs; int thread_enabled; TYPE_3__ dev; int /*<<< orphan*/  fm_buf; int /*<<< orphan*/  peb_buf; int /*<<< orphan*/  vtbl; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  bgt_thread; int /*<<< orphan*/  image_seq; int /*<<< orphan*/  mean_ec; int /*<<< orphan*/  max_ec; int /*<<< orphan*/  fm_size; int /*<<< orphan*/  fm_eba_sem; int /*<<< orphan*/  fm_protect; int /*<<< orphan*/  volumes_lock; int /*<<< orphan*/  device_mutex; int /*<<< orphan*/  ckvol_mutex; int /*<<< orphan*/  buf_mutex; TYPE_2__ fm_wl_pool; TYPE_1__ fm_pool; struct mtd_info* mtd; } ;
struct mtd_info {int index; scalar_t__ type; int name; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int CONFIG_MTD_UBI_BEB_LIMIT ; 
 int /*<<< orphan*/  CONFIG_MTD_UBI_WL_THRESHOLD ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENFILE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_MTD_UBI_BEB_LIMIT ; 
 scalar_t__ MTD_MLCNANDFLASH ; 
 scalar_t__ MTD_UBIVOLUME ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int UBI_DEV_NUM_AUTO ; 
 int /*<<< orphan*/  UBI_FM_MAX_POOL_SIZE ; 
 int UBI_FM_MAX_START ; 
 int /*<<< orphan*/  UBI_FM_MIN_POOL_SIZE ; 
 int UBI_INT_VOL_COUNT ; 
 int UBI_MAX_DEVICES ; 
 int /*<<< orphan*/  UBI_VOLUME_ADDED ; 
 int autoresize (struct ubi_device*,int) ; 
 int /*<<< orphan*/  dev_release ; 
 int /*<<< orphan*/  device_initialize (TYPE_3__*) ; 
 int /*<<< orphan*/  fm_autoconvert ; 
 scalar_t__ fm_debug ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int io_init (struct ubi_device*,int) ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ ,struct ubi_device*,char*,int) ; 
 struct ubi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mtd_div_by_eb (int /*<<< orphan*/ ,struct mtd_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ubi_attach (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_calc_fm_size (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_class ; 
 int /*<<< orphan*/  ubi_debugfs_exit_dev (struct ubi_device*) ; 
 int ubi_debugfs_init_dev (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_dev_groups ; 
 struct ubi_device** ubi_devices ; 
 int /*<<< orphan*/  ubi_enable_dbg_chk_fastmap (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int,...) ; 
 int /*<<< orphan*/  ubi_free_internal_volumes (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*,int,...) ; 
 int /*<<< orphan*/  ubi_notify_all (struct ubi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_thread ; 
 int /*<<< orphan*/  ubi_wl_close (struct ubi_device*) ; 
 int /*<<< orphan*/  uif_close (struct ubi_device*) ; 
 int uif_init (struct ubi_device*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc (int) ; 
 int /*<<< orphan*/  vzalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

int ubi_attach_mtd_dev(struct mtd_info *mtd, int ubi_num,
		       int vid_hdr_offset, int max_beb_per1024)
{
	struct ubi_device *ubi;
	int i, err;

	if (max_beb_per1024 < 0 || max_beb_per1024 > MAX_MTD_UBI_BEB_LIMIT)
		return -EINVAL;

	if (!max_beb_per1024)
		max_beb_per1024 = CONFIG_MTD_UBI_BEB_LIMIT;

	/*
	 * Check if we already have the same MTD device attached.
	 *
	 * Note, this function assumes that UBI devices creations and deletions
	 * are serialized, so it does not take the &ubi_devices_lock.
	 */
	for (i = 0; i < UBI_MAX_DEVICES; i++) {
		ubi = ubi_devices[i];
		if (ubi && mtd->index == ubi->mtd->index) {
			pr_err("ubi: mtd%d is already attached to ubi%d\n",
				mtd->index, i);
			return -EEXIST;
		}
	}

	/*
	 * Make sure this MTD device is not emulated on top of an UBI volume
	 * already. Well, generally this recursion works fine, but there are
	 * different problems like the UBI module takes a reference to itself
	 * by attaching (and thus, opening) the emulated MTD device. This
	 * results in inability to unload the module. And in general it makes
	 * no sense to attach emulated MTD devices, so we prohibit this.
	 */
	if (mtd->type == MTD_UBIVOLUME) {
		pr_err("ubi: refuse attaching mtd%d - it is already emulated on top of UBI\n",
			mtd->index);
		return -EINVAL;
	}

	/*
	 * Both UBI and UBIFS have been designed for SLC NAND and NOR flashes.
	 * MLC NAND is different and needs special care, otherwise UBI or UBIFS
	 * will die soon and you will lose all your data.
	 */
	if (mtd->type == MTD_MLCNANDFLASH) {
		pr_err("ubi: refuse attaching mtd%d - MLC NAND is not supported\n",
			mtd->index);
		return -EINVAL;
	}

	if (ubi_num == UBI_DEV_NUM_AUTO) {
		/* Search for an empty slot in the @ubi_devices array */
		for (ubi_num = 0; ubi_num < UBI_MAX_DEVICES; ubi_num++)
			if (!ubi_devices[ubi_num])
				break;
		if (ubi_num == UBI_MAX_DEVICES) {
			pr_err("ubi: only %d UBI devices may be created\n",
				UBI_MAX_DEVICES);
			return -ENFILE;
		}
	} else {
		if (ubi_num >= UBI_MAX_DEVICES)
			return -EINVAL;

		/* Make sure ubi_num is not busy */
		if (ubi_devices[ubi_num]) {
			pr_err("ubi: ubi%i already exists\n", ubi_num);
			return -EEXIST;
		}
	}

	ubi = kzalloc(sizeof(struct ubi_device), GFP_KERNEL);
	if (!ubi)
		return -ENOMEM;

	device_initialize(&ubi->dev);
	ubi->dev.release = dev_release;
	ubi->dev.class = &ubi_class;
	ubi->dev.groups = ubi_dev_groups;

	ubi->mtd = mtd;
	ubi->ubi_num = ubi_num;
	ubi->vid_hdr_offset = vid_hdr_offset;
	ubi->autoresize_vol_id = -1;

#ifdef CONFIG_MTD_UBI_FASTMAP
	ubi->fm_pool.used = ubi->fm_pool.size = 0;
	ubi->fm_wl_pool.used = ubi->fm_wl_pool.size = 0;

	/*
	 * fm_pool.max_size is 5% of the total number of PEBs but it's also
	 * between UBI_FM_MAX_POOL_SIZE and UBI_FM_MIN_POOL_SIZE.
	 */
	ubi->fm_pool.max_size = min(((int)mtd_div_by_eb(ubi->mtd->size,
		ubi->mtd) / 100) * 5, UBI_FM_MAX_POOL_SIZE);
	ubi->fm_pool.max_size = max(ubi->fm_pool.max_size,
		UBI_FM_MIN_POOL_SIZE);

	ubi->fm_wl_pool.max_size = ubi->fm_pool.max_size / 2;
	ubi->fm_disabled = !fm_autoconvert;
	if (fm_debug)
		ubi_enable_dbg_chk_fastmap(ubi);

	if (!ubi->fm_disabled && (int)mtd_div_by_eb(ubi->mtd->size, ubi->mtd)
	    <= UBI_FM_MAX_START) {
		ubi_err(ubi, "More than %i PEBs are needed for fastmap, sorry.",
			UBI_FM_MAX_START);
		ubi->fm_disabled = 1;
	}

	ubi_msg(ubi, "default fastmap pool size: %d", ubi->fm_pool.max_size);
	ubi_msg(ubi, "default fastmap WL pool size: %d",
		ubi->fm_wl_pool.max_size);
#else
	ubi->fm_disabled = 1;
#endif
	mutex_init(&ubi->buf_mutex);
	mutex_init(&ubi->ckvol_mutex);
	mutex_init(&ubi->device_mutex);
	spin_lock_init(&ubi->volumes_lock);
	init_rwsem(&ubi->fm_protect);
	init_rwsem(&ubi->fm_eba_sem);

	ubi_msg(ubi, "attaching mtd%d", mtd->index);

	err = io_init(ubi, max_beb_per1024);
	if (err)
		goto out_free;

	err = -ENOMEM;
	ubi->peb_buf = vmalloc(ubi->peb_size);
	if (!ubi->peb_buf)
		goto out_free;

#ifdef CONFIG_MTD_UBI_FASTMAP
	ubi->fm_size = ubi_calc_fm_size(ubi);
	ubi->fm_buf = vzalloc(ubi->fm_size);
	if (!ubi->fm_buf)
		goto out_free;
#endif
	err = ubi_attach(ubi, 0);
	if (err) {
		ubi_err(ubi, "failed to attach mtd%d, error %d",
			mtd->index, err);
		goto out_free;
	}

	if (ubi->autoresize_vol_id != -1) {
		err = autoresize(ubi, ubi->autoresize_vol_id);
		if (err)
			goto out_detach;
	}

	/* Make device "available" before it becomes accessible via sysfs */
	ubi_devices[ubi_num] = ubi;

	err = uif_init(ubi);
	if (err)
		goto out_detach;

	err = ubi_debugfs_init_dev(ubi);
	if (err)
		goto out_uif;

	ubi->bgt_thread = kthread_create(ubi_thread, ubi, "%s", ubi->bgt_name);
	if (IS_ERR(ubi->bgt_thread)) {
		err = PTR_ERR(ubi->bgt_thread);
		ubi_err(ubi, "cannot spawn \"%s\", error %d",
			ubi->bgt_name, err);
		goto out_debugfs;
	}

	ubi_msg(ubi, "attached mtd%d (name \"%s\", size %llu MiB)",
		mtd->index, mtd->name, ubi->flash_size >> 20);
	ubi_msg(ubi, "PEB size: %d bytes (%d KiB), LEB size: %d bytes",
		ubi->peb_size, ubi->peb_size >> 10, ubi->leb_size);
	ubi_msg(ubi, "min./max. I/O unit sizes: %d/%d, sub-page size %d",
		ubi->min_io_size, ubi->max_write_size, ubi->hdrs_min_io_size);
	ubi_msg(ubi, "VID header offset: %d (aligned %d), data offset: %d",
		ubi->vid_hdr_offset, ubi->vid_hdr_aloffset, ubi->leb_start);
	ubi_msg(ubi, "good PEBs: %d, bad PEBs: %d, corrupted PEBs: %d",
		ubi->good_peb_count, ubi->bad_peb_count, ubi->corr_peb_count);
	ubi_msg(ubi, "user volume: %d, internal volumes: %d, max. volumes count: %d",
		ubi->vol_count - UBI_INT_VOL_COUNT, UBI_INT_VOL_COUNT,
		ubi->vtbl_slots);
	ubi_msg(ubi, "max/mean erase counter: %d/%d, WL threshold: %d, image sequence number: %u",
		ubi->max_ec, ubi->mean_ec, CONFIG_MTD_UBI_WL_THRESHOLD,
		ubi->image_seq);
	ubi_msg(ubi, "available PEBs: %d, total reserved PEBs: %d, PEBs reserved for bad PEB handling: %d",
		ubi->avail_pebs, ubi->rsvd_pebs, ubi->beb_rsvd_pebs);

	/*
	 * The below lock makes sure we do not race with 'ubi_thread()' which
	 * checks @ubi->thread_enabled. Otherwise we may fail to wake it up.
	 */
	spin_lock(&ubi->wl_lock);
	ubi->thread_enabled = 1;
	wake_up_process(ubi->bgt_thread);
	spin_unlock(&ubi->wl_lock);

	ubi_notify_all(ubi, UBI_VOLUME_ADDED, NULL);
	return ubi_num;

out_debugfs:
	ubi_debugfs_exit_dev(ubi);
out_uif:
	uif_close(ubi);
out_detach:
	ubi_devices[ubi_num] = NULL;
	ubi_wl_close(ubi);
	ubi_free_internal_volumes(ubi);
	vfree(ubi->vtbl);
out_free:
	vfree(ubi->peb_buf);
	vfree(ubi->fm_buf);
	put_device(&ubi->dev);
	return err;
}