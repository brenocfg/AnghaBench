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
struct mddev {int /*<<< orphan*/  sync_set; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int) ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioset_initialized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bio *md_bio_alloc_sync(struct mddev *mddev)
{
	if (!mddev || !bioset_initialized(&mddev->sync_set))
		return bio_alloc(GFP_NOIO, 1);

	return bio_alloc_bioset(GFP_NOIO, 1, &mddev->sync_set);
}