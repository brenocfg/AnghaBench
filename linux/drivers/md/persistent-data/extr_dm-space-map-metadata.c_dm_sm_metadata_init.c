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
struct dm_space_map {int dummy; } ;
struct sm_metadata {struct dm_space_map sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dm_space_map* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sm_metadata* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct dm_space_map*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ops ; 

struct dm_space_map *dm_sm_metadata_init(void)
{
	struct sm_metadata *smm;

	smm = kmalloc(sizeof(*smm), GFP_KERNEL);
	if (!smm)
		return ERR_PTR(-ENOMEM);

	memcpy(&smm->sm, &ops, sizeof(smm->sm));

	return &smm->sm;
}