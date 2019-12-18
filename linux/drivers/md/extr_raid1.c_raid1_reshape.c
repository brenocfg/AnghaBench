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
struct raid1_info {int raid_disks; struct md_rdev* rdev; struct mddev* mddev; } ;
struct r1conf {int raid_disks; int /*<<< orphan*/  device_lock; struct raid1_info* poolinfo; struct raid1_info* mirrors; int /*<<< orphan*/  r1bio_pool; } ;
struct pool_info {int raid_disks; struct md_rdev* rdev; struct mddev* mddev; } ;
struct mddev {scalar_t__ chunk_sectors; scalar_t__ new_chunk_sectors; scalar_t__ layout; scalar_t__ new_layout; scalar_t__ level; scalar_t__ new_level; int raid_disks; int delta_disks; int degraded; int /*<<< orphan*/  thread; int /*<<< orphan*/  recovery; struct r1conf* private; } ;
struct md_rdev {int raid_disk; } ;
typedef  int /*<<< orphan*/  oldpool ;
typedef  int /*<<< orphan*/  newpool ;
typedef  int /*<<< orphan*/  mempool_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_RECOVERY_RECOVER ; 
 int /*<<< orphan*/  NR_RAID_BIOS ; 
 int /*<<< orphan*/  array3_size (int,int,int) ; 
 int /*<<< orphan*/  freeze_array (struct r1conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct raid1_info*) ; 
 struct raid1_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct raid1_info* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_allow_write (struct mddev*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddev_is_clustered (struct mddev*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int mempool_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct raid1_info*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r1bio_pool_alloc ; 
 int /*<<< orphan*/  rbio_pool_free ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ sysfs_link_rdev (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  sysfs_unlink_rdev (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  unfreeze_array (struct r1conf*) ; 

__attribute__((used)) static int raid1_reshape(struct mddev *mddev)
{
	/* We need to:
	 * 1/ resize the r1bio_pool
	 * 2/ resize conf->mirrors
	 *
	 * We allocate a new r1bio_pool if we can.
	 * Then raise a device barrier and wait until all IO stops.
	 * Then resize conf->mirrors and swap in the new r1bio pool.
	 *
	 * At the same time, we "pack" the devices so that all the missing
	 * devices have the higher raid_disk numbers.
	 */
	mempool_t newpool, oldpool;
	struct pool_info *newpoolinfo;
	struct raid1_info *newmirrors;
	struct r1conf *conf = mddev->private;
	int cnt, raid_disks;
	unsigned long flags;
	int d, d2;
	int ret;

	memset(&newpool, 0, sizeof(newpool));
	memset(&oldpool, 0, sizeof(oldpool));

	/* Cannot change chunk_size, layout, or level */
	if (mddev->chunk_sectors != mddev->new_chunk_sectors ||
	    mddev->layout != mddev->new_layout ||
	    mddev->level != mddev->new_level) {
		mddev->new_chunk_sectors = mddev->chunk_sectors;
		mddev->new_layout = mddev->layout;
		mddev->new_level = mddev->level;
		return -EINVAL;
	}

	if (!mddev_is_clustered(mddev))
		md_allow_write(mddev);

	raid_disks = mddev->raid_disks + mddev->delta_disks;

	if (raid_disks < conf->raid_disks) {
		cnt=0;
		for (d= 0; d < conf->raid_disks; d++)
			if (conf->mirrors[d].rdev)
				cnt++;
		if (cnt > raid_disks)
			return -EBUSY;
	}

	newpoolinfo = kmalloc(sizeof(*newpoolinfo), GFP_KERNEL);
	if (!newpoolinfo)
		return -ENOMEM;
	newpoolinfo->mddev = mddev;
	newpoolinfo->raid_disks = raid_disks * 2;

	ret = mempool_init(&newpool, NR_RAID_BIOS, r1bio_pool_alloc,
			   rbio_pool_free, newpoolinfo);
	if (ret) {
		kfree(newpoolinfo);
		return ret;
	}
	newmirrors = kzalloc(array3_size(sizeof(struct raid1_info),
					 raid_disks, 2),
			     GFP_KERNEL);
	if (!newmirrors) {
		kfree(newpoolinfo);
		mempool_exit(&newpool);
		return -ENOMEM;
	}

	freeze_array(conf, 0);

	/* ok, everything is stopped */
	oldpool = conf->r1bio_pool;
	conf->r1bio_pool = newpool;

	for (d = d2 = 0; d < conf->raid_disks; d++) {
		struct md_rdev *rdev = conf->mirrors[d].rdev;
		if (rdev && rdev->raid_disk != d2) {
			sysfs_unlink_rdev(mddev, rdev);
			rdev->raid_disk = d2;
			sysfs_unlink_rdev(mddev, rdev);
			if (sysfs_link_rdev(mddev, rdev))
				pr_warn("md/raid1:%s: cannot register rd%d\n",
					mdname(mddev), rdev->raid_disk);
		}
		if (rdev)
			newmirrors[d2++].rdev = rdev;
	}
	kfree(conf->mirrors);
	conf->mirrors = newmirrors;
	kfree(conf->poolinfo);
	conf->poolinfo = newpoolinfo;

	spin_lock_irqsave(&conf->device_lock, flags);
	mddev->degraded += (raid_disks - conf->raid_disks);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	conf->raid_disks = mddev->raid_disks = raid_disks;
	mddev->delta_disks = 0;

	unfreeze_array(conf);

	set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_wakeup_thread(mddev->thread);

	mempool_exit(&oldpool);
	return 0;
}