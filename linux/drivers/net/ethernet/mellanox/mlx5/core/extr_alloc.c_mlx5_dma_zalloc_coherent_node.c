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
struct mlx5_priv {int /*<<< orphan*/  alloc_mutex; } ;
struct mlx5_core_dev {struct device* device; struct mlx5_priv priv; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dev_to_node (struct device*) ; 
 void* dma_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dev_node (struct device*,int) ; 

__attribute__((used)) static void *mlx5_dma_zalloc_coherent_node(struct mlx5_core_dev *dev,
					   size_t size, dma_addr_t *dma_handle,
					   int node)
{
	struct mlx5_priv *priv = &dev->priv;
	struct device *device = dev->device;
	int original_node;
	void *cpu_handle;

	mutex_lock(&priv->alloc_mutex);
	original_node = dev_to_node(device);
	set_dev_node(device, node);
	cpu_handle = dma_alloc_coherent(device, size, dma_handle,
					GFP_KERNEL);
	set_dev_node(device, original_node);
	mutex_unlock(&priv->alloc_mutex);
	return cpu_handle;
}