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
struct mlx5_geneve {scalar_t__ refcount; int /*<<< orphan*/  sync_lock; scalar_t__ obj_id; scalar_t__ opt_type; scalar_t__ opt_class; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_geneve*) ; 
 int /*<<< orphan*/  mlx5_geneve_tlv_option_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5_geneve_tlv_option_del(struct mlx5_geneve *geneve)
{
	if (IS_ERR_OR_NULL(geneve))
		return;

	mutex_lock(&geneve->sync_lock);
	if (--geneve->refcount == 0) {
		/* We've just removed the last user of Geneve option.
		 * Now delete the object in FW.
		 */
		mlx5_geneve_tlv_option_destroy(geneve->mdev, geneve->obj_id);

		geneve->opt_class = 0;
		geneve->opt_type = 0;
		geneve->obj_id = 0;
	}
	mutex_unlock(&geneve->sync_lock);
}