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
struct TYPE_2__ {int nodes; } ;
struct mddev {TYPE_1__ bitmap_info; struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {scalar_t__* other_bitmap_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  lockres_free (scalar_t__) ; 

__attribute__((used)) static void unlock_all_bitmaps(struct mddev *mddev)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;
	int i;

	/* release other node's bitmap lock if they are existed */
	if (cinfo->other_bitmap_lockres) {
		for (i = 0; i < mddev->bitmap_info.nodes - 1; i++) {
			if (cinfo->other_bitmap_lockres[i]) {
				lockres_free(cinfo->other_bitmap_lockres[i]);
			}
		}
		kfree(cinfo->other_bitmap_lockres);
	}
}