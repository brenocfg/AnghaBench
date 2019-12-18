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
struct r5conf {struct ppl_conf* log_private; } ;
struct ppl_conf {unsigned short write_hint; } ;
struct mddev {struct r5conf* private; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t PAGE_SIZE ; 
 scalar_t__ kstrtou16 (char const*,int,unsigned short*) ; 
 int mddev_lock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 scalar_t__ raid5_has_ppl (struct r5conf*) ; 

__attribute__((used)) static ssize_t
ppl_write_hint_store(struct mddev *mddev, const char *page, size_t len)
{
	struct r5conf *conf;
	struct ppl_conf *ppl_conf;
	int err = 0;
	unsigned short new;

	if (len >= PAGE_SIZE)
		return -EINVAL;
	if (kstrtou16(page, 10, &new))
		return -EINVAL;

	err = mddev_lock(mddev);
	if (err)
		return err;

	conf = mddev->private;
	if (!conf) {
		err = -ENODEV;
	} else if (raid5_has_ppl(conf)) {
		ppl_conf = conf->log_private;
		if (!ppl_conf)
			err = -EINVAL;
		else
			ppl_conf->write_hint = new;
	} else {
		err = -EINVAL;
	}

	mddev_unlock(mddev);

	return err ?: len;
}