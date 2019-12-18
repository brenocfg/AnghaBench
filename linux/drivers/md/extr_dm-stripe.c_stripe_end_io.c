#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stripe_c {unsigned int stripes; int /*<<< orphan*/  trigger_event; TYPE_2__* stripe; } ;
struct dm_target {struct stripe_c* private; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  major_minor ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  error_count; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_NOTSUPP ; 
 int DM_ENDIO_DONE ; 
 scalar_t__ DM_IO_ERROR_THRESHOLD ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_dev (struct bio*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int stripe_end_io(struct dm_target *ti, struct bio *bio,
		blk_status_t *error)
{
	unsigned i;
	char major_minor[16];
	struct stripe_c *sc = ti->private;

	if (!*error)
		return DM_ENDIO_DONE; /* I/O complete */

	if (bio->bi_opf & REQ_RAHEAD)
		return DM_ENDIO_DONE;

	if (*error == BLK_STS_NOTSUPP)
		return DM_ENDIO_DONE;

	memset(major_minor, 0, sizeof(major_minor));
	sprintf(major_minor, "%d:%d", MAJOR(bio_dev(bio)), MINOR(bio_dev(bio)));

	/*
	 * Test to see which stripe drive triggered the event
	 * and increment error count for all stripes on that device.
	 * If the error count for a given device exceeds the threshold
	 * value we will no longer trigger any further events.
	 */
	for (i = 0; i < sc->stripes; i++)
		if (!strcmp(sc->stripe[i].dev->name, major_minor)) {
			atomic_inc(&(sc->stripe[i].error_count));
			if (atomic_read(&(sc->stripe[i].error_count)) <
			    DM_IO_ERROR_THRESHOLD)
				schedule_work(&sc->trigger_event);
		}

	return DM_ENDIO_DONE;
}