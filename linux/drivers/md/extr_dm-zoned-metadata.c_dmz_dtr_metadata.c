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
struct dmz_metadata {int /*<<< orphan*/  mblk_shrinker; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmz_cleanup_metadata (struct dmz_metadata*) ; 
 int /*<<< orphan*/  kfree (struct dmz_metadata*) ; 
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 

void dmz_dtr_metadata(struct dmz_metadata *zmd)
{
	unregister_shrinker(&zmd->mblk_shrinker);
	dmz_cleanup_metadata(zmd);
	kfree(zmd);
}