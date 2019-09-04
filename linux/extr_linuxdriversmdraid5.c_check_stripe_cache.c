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
struct r5conf {int min_nr_stripes; } ;
struct mddev {int chunk_sectors; int new_chunk_sectors; struct r5conf* private; } ;

/* Variables and functions */
 int STRIPE_SIZE ; 
 int max (int,int) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_stripe_cache(struct mddev *mddev)
{
	/* Can only proceed if there are plenty of stripe_heads.
	 * We need a minimum of one full stripe,, and for sensible progress
	 * it is best to have about 4 times that.
	 * If we require 4 times, then the default 256 4K stripe_heads will
	 * allow for chunk sizes up to 256K, which is probably OK.
	 * If the chunk size is greater, user-space should request more
	 * stripe_heads first.
	 */
	struct r5conf *conf = mddev->private;
	if (((mddev->chunk_sectors << 9) / STRIPE_SIZE) * 4
	    > conf->min_nr_stripes ||
	    ((mddev->new_chunk_sectors << 9) / STRIPE_SIZE) * 4
	    > conf->min_nr_stripes) {
		pr_warn("md/raid:%s: reshape: not enough stripes.  Needed %lu\n",
			mdname(mddev),
			((max(mddev->chunk_sectors, mddev->new_chunk_sectors) << 9)
			 / STRIPE_SIZE)*4);
		return 0;
	}
	return 1;
}