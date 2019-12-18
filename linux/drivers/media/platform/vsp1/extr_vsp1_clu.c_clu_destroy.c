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
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct vsp1_clu {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 struct vsp1_clu* to_clu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_dl_body_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clu_destroy(struct vsp1_entity *entity)
{
	struct vsp1_clu *clu = to_clu(&entity->subdev);

	vsp1_dl_body_pool_destroy(clu->pool);
}