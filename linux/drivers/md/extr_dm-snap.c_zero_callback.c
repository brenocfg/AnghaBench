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
struct dm_snapshot {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_status; struct dm_snapshot* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  account_end_copy (struct dm_snapshot*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 

__attribute__((used)) static void zero_callback(int read_err, unsigned long write_err, void *context)
{
	struct bio *bio = context;
	struct dm_snapshot *s = bio->bi_private;

	account_end_copy(s);
	bio->bi_status = write_err ? BLK_STS_IOERR : 0;
	bio_endio(bio);
}