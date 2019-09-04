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
struct dm_pool_metadata {int /*<<< orphan*/  bm; int /*<<< orphan*/  tm; int /*<<< orphan*/  nb_tm; int /*<<< orphan*/  metadata_sm; int /*<<< orphan*/  data_sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_block_manager_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_sm_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __destroy_persistent_data_objects(struct dm_pool_metadata *pmd)
{
	dm_sm_destroy(pmd->data_sm);
	dm_sm_destroy(pmd->metadata_sm);
	dm_tm_destroy(pmd->nb_tm);
	dm_tm_destroy(pmd->tm);
	dm_block_manager_destroy(pmd->bm);
}