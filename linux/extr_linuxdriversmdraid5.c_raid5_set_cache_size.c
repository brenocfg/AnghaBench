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
struct r5conf {int min_nr_stripes; int max_nr_stripes; int /*<<< orphan*/  cache_size_mutex; } ;
struct mddev {struct r5conf* private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ drop_one_stripe (struct r5conf*) ; 
 int /*<<< orphan*/  grow_one_stripe (struct r5conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_allow_write (struct mddev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
raid5_set_cache_size(struct mddev *mddev, int size)
{
	int result = 0;
	struct r5conf *conf = mddev->private;

	if (size <= 16 || size > 32768)
		return -EINVAL;

	conf->min_nr_stripes = size;
	mutex_lock(&conf->cache_size_mutex);
	while (size < conf->max_nr_stripes &&
	       drop_one_stripe(conf))
		;
	mutex_unlock(&conf->cache_size_mutex);

	md_allow_write(mddev);

	mutex_lock(&conf->cache_size_mutex);
	while (size > conf->max_nr_stripes)
		if (!grow_one_stripe(conf, GFP_KERNEL)) {
			conf->min_nr_stripes = conf->max_nr_stripes;
			result = -ENOMEM;
			break;
		}
	mutex_unlock(&conf->cache_size_mutex);

	return result;
}