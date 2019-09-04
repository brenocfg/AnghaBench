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
struct superblock_disk {int /*<<< orphan*/  metadata_space_map_root; } ;
struct era_metadata {int /*<<< orphan*/  metadata_space_map_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_sm_root(struct era_metadata *md, struct superblock_disk *disk)
{
	memcpy(&disk->metadata_space_map_root,
	       &md->metadata_space_map_root,
	       sizeof(md->metadata_space_map_root));
}