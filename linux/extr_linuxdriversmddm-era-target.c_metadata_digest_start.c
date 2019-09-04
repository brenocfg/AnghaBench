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
struct era_metadata {int /*<<< orphan*/  tm; } ;
struct digest {scalar_t__ step; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_disk_bitset_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct digest*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ metadata_digest_lookup_writeset ; 

__attribute__((used)) static int metadata_digest_start(struct era_metadata *md, struct digest *d)
{
	if (d->step)
		return 0;

	memset(d, 0, sizeof(*d));

	/*
	 * We initialise another bitset info to avoid any caching side
	 * effects with the previous one.
	 */
	dm_disk_bitset_init(md->tm, &d->info);
	d->step = metadata_digest_lookup_writeset;

	return 0;
}