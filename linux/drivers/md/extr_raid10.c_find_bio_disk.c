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
struct r10conf {int copies; } ;
struct r10bio {TYPE_1__* devs; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int devnum; struct bio* repl_bio; struct bio* bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  update_head_pos (int,struct r10bio*) ; 

__attribute__((used)) static int find_bio_disk(struct r10conf *conf, struct r10bio *r10_bio,
			 struct bio *bio, int *slotp, int *replp)
{
	int slot;
	int repl = 0;

	for (slot = 0; slot < conf->copies; slot++) {
		if (r10_bio->devs[slot].bio == bio)
			break;
		if (r10_bio->devs[slot].repl_bio == bio) {
			repl = 1;
			break;
		}
	}

	BUG_ON(slot == conf->copies);
	update_head_pos(slot, r10_bio);

	if (slotp)
		*slotp = slot;
	if (replp)
		*replp = repl;
	return r10_bio->devs[slot].devnum;
}