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
struct mddev {unsigned long long recovery_cp; int /*<<< orphan*/  sb_flags; scalar_t__ pers; int /*<<< orphan*/  recovery; } ;
typedef  int ssize_t ;
typedef  unsigned long long sector_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  MD_SB_CHANGE_CLEAN ; 
 unsigned long long MaxSector ; 
 scalar_t__ cmd_match (char const*,char*) ; 
 int kstrtoull (char const*,int,unsigned long long*) ; 
 int mddev_lock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
resync_start_store(struct mddev *mddev, const char *buf, size_t len)
{
	unsigned long long n;
	int err;

	if (cmd_match(buf, "none"))
		n = MaxSector;
	else {
		err = kstrtoull(buf, 10, &n);
		if (err < 0)
			return err;
		if (n != (sector_t)n)
			return -EINVAL;
	}

	err = mddev_lock(mddev);
	if (err)
		return err;
	if (mddev->pers && !test_bit(MD_RECOVERY_FROZEN, &mddev->recovery))
		err = -EBUSY;

	if (!err) {
		mddev->recovery_cp = n;
		if (mddev->pers)
			set_bit(MD_SB_CHANGE_CLEAN, &mddev->sb_flags);
	}
	mddev_unlock(mddev);
	return err ?: len;
}