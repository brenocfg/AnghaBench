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
struct ppl_conf {int write_hint; } ;
struct mddev {int /*<<< orphan*/  lock; struct r5conf* private; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ raid5_has_ppl (struct r5conf*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 size_t sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t
ppl_write_hint_show(struct mddev *mddev, char *buf)
{
	size_t ret = 0;
	struct r5conf *conf;
	struct ppl_conf *ppl_conf = NULL;

	spin_lock(&mddev->lock);
	conf = mddev->private;
	if (conf && raid5_has_ppl(conf))
		ppl_conf = conf->log_private;
	ret = sprintf(buf, "%d\n", ppl_conf ? ppl_conf->write_hint : 0);
	spin_unlock(&mddev->lock);

	return ret;
}