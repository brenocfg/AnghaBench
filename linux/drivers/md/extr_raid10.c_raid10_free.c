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
struct r10conf {int /*<<< orphan*/  bio_split; struct r10conf* mirrors_new; struct r10conf* mirrors_old; struct r10conf* mirrors; int /*<<< orphan*/  tmppage; int /*<<< orphan*/  r10bio_pool; } ;
struct mddev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct r10conf*) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raid10_free(struct mddev *mddev, void *priv)
{
	struct r10conf *conf = priv;

	mempool_exit(&conf->r10bio_pool);
	safe_put_page(conf->tmppage);
	kfree(conf->mirrors);
	kfree(conf->mirrors_old);
	kfree(conf->mirrors_new);
	bioset_exit(&conf->bio_split);
	kfree(conf);
}