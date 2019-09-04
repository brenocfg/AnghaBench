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
struct r10conf {int dummy; } ;
struct r10bio {TYPE_1__* mddev; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {struct r10conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  __end_sync_read (struct r10bio*,struct bio*,int) ; 
 int find_bio_disk (struct r10conf*,struct r10bio*,struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct r10bio* get_resync_r10bio (struct bio*) ; 

__attribute__((used)) static void end_sync_read(struct bio *bio)
{
	struct r10bio *r10_bio = get_resync_r10bio(bio);
	struct r10conf *conf = r10_bio->mddev->private;
	int d = find_bio_disk(conf, r10_bio, bio, NULL, NULL);

	__end_sync_read(r10_bio, bio, d);
}