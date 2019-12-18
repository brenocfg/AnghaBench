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
struct r10conf {scalar_t__ reshape_progress; } ;
struct mddev {scalar_t__ reshape_position; struct r10conf* private; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* resync_info_get ) (struct mddev*,scalar_t__*,scalar_t__*) ;} ;

/* Variables and functions */
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_1__* md_cluster_ops ; 
 int /*<<< orphan*/  stub1 (struct mddev*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void raid10_update_reshape_pos(struct mddev *mddev)
{
	struct r10conf *conf = mddev->private;
	sector_t lo, hi;

	md_cluster_ops->resync_info_get(mddev, &lo, &hi);
	if (((mddev->reshape_position <= hi) && (mddev->reshape_position >= lo))
	    || mddev->reshape_position == MaxSector)
		conf->reshape_progress = mddev->reshape_position;
	else
		WARN_ON_ONCE(1);
}