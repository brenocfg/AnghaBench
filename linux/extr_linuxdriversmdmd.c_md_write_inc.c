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
struct mddev {int /*<<< orphan*/  writes_pending; scalar_t__ ro; scalar_t__ in_sync; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  percpu_ref_get (int /*<<< orphan*/ *) ; 

void md_write_inc(struct mddev *mddev, struct bio *bi)
{
	if (bio_data_dir(bi) != WRITE)
		return;
	WARN_ON_ONCE(mddev->in_sync || mddev->ro);
	percpu_ref_get(&mddev->writes_pending);
}