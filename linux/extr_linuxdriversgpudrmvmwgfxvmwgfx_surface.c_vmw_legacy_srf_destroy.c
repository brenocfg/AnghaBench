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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_resource {int id; scalar_t__ backup_size; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  used_memory_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_fifo_commit (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmw_fifo_reserve (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fifo_resource_dec (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_resource_release_id (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_surface_destroy_encode (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_surface_destroy_size () ; 

__attribute__((used)) static int vmw_legacy_srf_destroy(struct vmw_resource *res)
{
	struct vmw_private *dev_priv = res->dev_priv;
	uint32_t submit_size;
	uint8_t *cmd;

	BUG_ON(res->id == -1);

	/*
	 * Encode the dma- and surface destroy commands.
	 */

	submit_size = vmw_surface_destroy_size();
	cmd = vmw_fifo_reserve(dev_priv, submit_size);
	if (unlikely(!cmd)) {
		DRM_ERROR("Failed reserving FIFO space for surface "
			  "eviction.\n");
		return -ENOMEM;
	}

	vmw_surface_destroy_encode(res->id, cmd);
	vmw_fifo_commit(dev_priv, submit_size);

	/*
	 * Surface memory usage accounting.
	 */

	dev_priv->used_memory_size -= res->backup_size;

	/*
	 * Release the surface ID.
	 */

	vmw_resource_release_id(res);
	vmw_fifo_resource_dec(dev_priv);

	return 0;
}