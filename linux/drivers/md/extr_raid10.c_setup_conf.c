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
struct raid10_info {int dummy; } ;
struct geom {int stride; int chunk_shift; scalar_t__ far_offset; } ;
struct r10conf {int copies; scalar_t__ reshape_progress; int dev_sectors; scalar_t__ reshape_safe; int /*<<< orphan*/  bio_split; int /*<<< orphan*/  tmppage; struct r10conf* mirrors; int /*<<< orphan*/  r10bio_pool; struct mddev* mddev; int /*<<< orphan*/  thread; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  resync_lock; int /*<<< orphan*/  bio_end_io_list; int /*<<< orphan*/  retry_list; int /*<<< orphan*/  device_lock; struct geom prev; struct geom geo; } ;
struct mddev {int raid_disks; scalar_t__ reshape_position; int /*<<< orphan*/  dev_sectors; int /*<<< orphan*/  delta_disks; int /*<<< orphan*/  new_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_POOL_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct r10conf* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  NR_RAID_BIOS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int bioset_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calc_sectors (struct r10conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geo_new ; 
 int /*<<< orphan*/  geo_old ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct r10conf* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct r10conf*) ; 
 struct r10conf* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_register_thread (int /*<<< orphan*/ ,struct mddev*,char*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int mempool_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct r10conf*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r10bio_pool_alloc ; 
 int /*<<< orphan*/  raid10d ; 
 int /*<<< orphan*/  rbio_pool_free ; 
 int /*<<< orphan*/  safe_put_page (int /*<<< orphan*/ ) ; 
 int setup_geo (struct geom*,struct mddev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct r10conf *setup_conf(struct mddev *mddev)
{
	struct r10conf *conf = NULL;
	int err = -EINVAL;
	struct geom geo;
	int copies;

	copies = setup_geo(&geo, mddev, geo_new);

	if (copies == -2) {
		pr_warn("md/raid10:%s: chunk size must be at least PAGE_SIZE(%ld) and be a power of 2.\n",
			mdname(mddev), PAGE_SIZE);
		goto out;
	}

	if (copies < 2 || copies > mddev->raid_disks) {
		pr_warn("md/raid10:%s: unsupported raid10 layout: 0x%8x\n",
			mdname(mddev), mddev->new_layout);
		goto out;
	}

	err = -ENOMEM;
	conf = kzalloc(sizeof(struct r10conf), GFP_KERNEL);
	if (!conf)
		goto out;

	/* FIXME calc properly */
	conf->mirrors = kcalloc(mddev->raid_disks + max(0, -mddev->delta_disks),
				sizeof(struct raid10_info),
				GFP_KERNEL);
	if (!conf->mirrors)
		goto out;

	conf->tmppage = alloc_page(GFP_KERNEL);
	if (!conf->tmppage)
		goto out;

	conf->geo = geo;
	conf->copies = copies;
	err = mempool_init(&conf->r10bio_pool, NR_RAID_BIOS, r10bio_pool_alloc,
			   rbio_pool_free, conf);
	if (err)
		goto out;

	err = bioset_init(&conf->bio_split, BIO_POOL_SIZE, 0, 0);
	if (err)
		goto out;

	calc_sectors(conf, mddev->dev_sectors);
	if (mddev->reshape_position == MaxSector) {
		conf->prev = conf->geo;
		conf->reshape_progress = MaxSector;
	} else {
		if (setup_geo(&conf->prev, mddev, geo_old) != conf->copies) {
			err = -EINVAL;
			goto out;
		}
		conf->reshape_progress = mddev->reshape_position;
		if (conf->prev.far_offset)
			conf->prev.stride = 1 << conf->prev.chunk_shift;
		else
			/* far_copies must be 1 */
			conf->prev.stride = conf->dev_sectors;
	}
	conf->reshape_safe = conf->reshape_progress;
	spin_lock_init(&conf->device_lock);
	INIT_LIST_HEAD(&conf->retry_list);
	INIT_LIST_HEAD(&conf->bio_end_io_list);

	spin_lock_init(&conf->resync_lock);
	init_waitqueue_head(&conf->wait_barrier);
	atomic_set(&conf->nr_pending, 0);

	err = -ENOMEM;
	conf->thread = md_register_thread(raid10d, mddev, "raid10");
	if (!conf->thread)
		goto out;

	conf->mddev = mddev;
	return conf;

 out:
	if (conf) {
		mempool_exit(&conf->r10bio_pool);
		kfree(conf->mirrors);
		safe_put_page(conf->tmppage);
		bioset_exit(&conf->bio_split);
		kfree(conf);
	}
	return ERR_PTR(err);
}