#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resync_pages {int dummy; } ;
struct r10conf {int copies; } ;
struct r10bio {TYPE_1__* devs; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {struct bio* repl_bio; struct bio* bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 struct resync_pages* get_resync_pages (struct bio*) ; 
 int /*<<< orphan*/  kfree (struct resync_pages*) ; 
 int /*<<< orphan*/  rbio_pool_free (struct r10bio*,struct r10conf*) ; 
 int /*<<< orphan*/  resync_free_pages (struct resync_pages*) ; 

__attribute__((used)) static void r10buf_pool_free(void *__r10_bio, void *data)
{
	struct r10conf *conf = data;
	struct r10bio *r10bio = __r10_bio;
	int j;
	struct resync_pages *rp = NULL;

	for (j = conf->copies; j--; ) {
		struct bio *bio = r10bio->devs[j].bio;

		if (bio) {
			rp = get_resync_pages(bio);
			resync_free_pages(rp);
			bio_put(bio);
		}

		bio = r10bio->devs[j].repl_bio;
		if (bio)
			bio_put(bio);
	}

	/* resync pages array stored in the 1st bio's .bi_private */
	kfree(rp);

	rbio_pool_free(r10bio, conf);
}