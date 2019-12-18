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
struct r5conf {int pool_size; struct r5conf* pending_data; struct r5conf* stripe_hashtbl; int /*<<< orphan*/  bio_split; struct r5conf* disks; scalar_t__ extra_page; int /*<<< orphan*/  shrinker; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_thread_groups (struct r5conf*) ; 
 int /*<<< orphan*/  kfree (struct r5conf*) ; 
 int /*<<< orphan*/  log_exit (struct r5conf*) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 
 int /*<<< orphan*/  raid5_free_percpu (struct r5conf*) ; 
 int /*<<< orphan*/  shrink_stripes (struct r5conf*) ; 
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_conf(struct r5conf *conf)
{
	int i;

	log_exit(conf);

	unregister_shrinker(&conf->shrinker);
	free_thread_groups(conf);
	shrink_stripes(conf);
	raid5_free_percpu(conf);
	for (i = 0; i < conf->pool_size; i++)
		if (conf->disks[i].extra_page)
			put_page(conf->disks[i].extra_page);
	kfree(conf->disks);
	bioset_exit(&conf->bio_split);
	kfree(conf->stripe_hashtbl);
	kfree(conf->pending_data);
	kfree(conf);
}