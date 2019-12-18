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
struct r1conf {int /*<<< orphan*/  bio_split; struct r1conf* barrier; struct r1conf* nr_queued; struct r1conf* nr_waiting; struct r1conf* nr_pending; struct r1conf* poolinfo; int /*<<< orphan*/  tmppage; struct r1conf* mirrors; int /*<<< orphan*/  r1bio_pool; } ;
struct mddev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct r1conf*) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raid1_free(struct mddev *mddev, void *priv)
{
	struct r1conf *conf = priv;

	mempool_exit(&conf->r1bio_pool);
	kfree(conf->mirrors);
	safe_put_page(conf->tmppage);
	kfree(conf->poolinfo);
	kfree(conf->nr_pending);
	kfree(conf->nr_waiting);
	kfree(conf->nr_queued);
	kfree(conf->barrier);
	bioset_exit(&conf->bio_split);
	kfree(conf);
}