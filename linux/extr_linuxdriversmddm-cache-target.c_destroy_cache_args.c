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
struct cache_args {scalar_t__ origin_dev; int /*<<< orphan*/  ti; scalar_t__ cache_dev; scalar_t__ metadata_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cache_args*) ; 

__attribute__((used)) static void destroy_cache_args(struct cache_args *ca)
{
	if (ca->metadata_dev)
		dm_put_device(ca->ti, ca->metadata_dev);

	if (ca->cache_dev)
		dm_put_device(ca->ti, ca->cache_dev);

	if (ca->origin_dev)
		dm_put_device(ca->ti, ca->origin_dev);

	kfree(ca);
}