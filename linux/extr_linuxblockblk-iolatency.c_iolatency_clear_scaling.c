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
struct child_latency_info {int /*<<< orphan*/  lock; scalar_t__ scale_lat; int /*<<< orphan*/ * scale_grp; scalar_t__ last_scale_event; int /*<<< orphan*/  scale_cookie; } ;
struct iolatency_grp {struct child_latency_info child_lat; } ;
struct blkcg_gq {scalar_t__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SCALE_COOKIE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iolatency_grp* blkg_to_lat (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iolatency_clear_scaling(struct blkcg_gq *blkg)
{
	if (blkg->parent) {
		struct iolatency_grp *iolat = blkg_to_lat(blkg->parent);
		struct child_latency_info *lat_info;
		if (!iolat)
			return;

		lat_info = &iolat->child_lat;
		spin_lock(&lat_info->lock);
		atomic_set(&lat_info->scale_cookie, DEFAULT_SCALE_COOKIE);
		lat_info->last_scale_event = 0;
		lat_info->scale_grp = NULL;
		lat_info->scale_lat = 0;
		spin_unlock(&lat_info->lock);
	}
}