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
struct era_metadata {int /*<<< orphan*/  bitset_info; int /*<<< orphan*/  tm; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_disk_bitset_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_era_array_info (struct era_metadata*) ; 
 int /*<<< orphan*/  setup_writeset_tree_info (struct era_metadata*) ; 

__attribute__((used)) static void setup_infos(struct era_metadata *md)
{
	dm_disk_bitset_init(md->tm, &md->bitset_info);
	setup_writeset_tree_info(md);
	setup_era_array_info(md);
}