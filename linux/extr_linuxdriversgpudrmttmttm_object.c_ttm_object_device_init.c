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
struct dma_buf_ops {int /*<<< orphan*/  release; } ;
struct ttm_object_device {scalar_t__ dma_buf_size; struct dma_buf_ops ops; int /*<<< orphan*/  dmabuf_release; int /*<<< orphan*/  object_hash; int /*<<< orphan*/  object_count; int /*<<< orphan*/  object_lock; struct ttm_mem_global* mem_glob; } ;
struct ttm_mem_global {int dummy; } ;
struct file {int dummy; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_ht_create (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct ttm_object_device*) ; 
 struct ttm_object_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_prime_dmabuf_release ; 
 scalar_t__ ttm_round_pot (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct ttm_object_device *
ttm_object_device_init(struct ttm_mem_global *mem_glob,
		       unsigned int hash_order,
		       const struct dma_buf_ops *ops)
{
	struct ttm_object_device *tdev = kmalloc(sizeof(*tdev), GFP_KERNEL);
	int ret;

	if (unlikely(tdev == NULL))
		return NULL;

	tdev->mem_glob = mem_glob;
	spin_lock_init(&tdev->object_lock);
	atomic_set(&tdev->object_count, 0);
	ret = drm_ht_create(&tdev->object_hash, hash_order);
	if (ret != 0)
		goto out_no_object_hash;

	tdev->ops = *ops;
	tdev->dmabuf_release = tdev->ops.release;
	tdev->ops.release = ttm_prime_dmabuf_release;
	tdev->dma_buf_size = ttm_round_pot(sizeof(struct dma_buf)) +
		ttm_round_pot(sizeof(struct file));
	return tdev;

out_no_object_hash:
	kfree(tdev);
	return NULL;
}