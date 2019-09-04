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
struct dm_snap_tracked_chunk {int /*<<< orphan*/  node; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct dm_snap_tracked_chunk* dm_per_bio_data (struct bio*,int) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool is_bio_tracked(struct bio *bio)
{
	struct dm_snap_tracked_chunk *c = dm_per_bio_data(bio, sizeof(struct dm_snap_tracked_chunk));
	return !hlist_unhashed(&c->node);
}