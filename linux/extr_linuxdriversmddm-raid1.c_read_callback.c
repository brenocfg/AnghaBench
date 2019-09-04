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
struct mirror {TYPE_1__* dev; int /*<<< orphan*/  ms; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR_LIMIT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMWARN_LIMIT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DM_RAID1_READ_ERROR ; 
 int /*<<< orphan*/  bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 struct mirror* bio_get_m (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_set_m (struct bio*,int /*<<< orphan*/ *) ; 
 int default_ok (struct mirror*) ; 
 int /*<<< orphan*/  fail_mirror (struct mirror*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ mirror_available (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  queue_bio (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_callback(unsigned long error, void *context)
{
	struct bio *bio = context;
	struct mirror *m;

	m = bio_get_m(bio);
	bio_set_m(bio, NULL);

	if (likely(!error)) {
		bio_endio(bio);
		return;
	}

	fail_mirror(m, DM_RAID1_READ_ERROR);

	if (likely(default_ok(m)) || mirror_available(m->ms, bio)) {
		DMWARN_LIMIT("Read failure on mirror device %s.  "
			     "Trying alternative device.",
			     m->dev->name);
		queue_bio(m->ms, bio, bio_data_dir(bio));
		return;
	}

	DMERR_LIMIT("Read failure on mirror device %s.  Failing I/O.",
		    m->dev->name);
	bio_io_error(bio);
}