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
struct tee_shm {int flags; int /*<<< orphan*/  dmabuf; struct tee_context* ctx; } ;
struct tee_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  idr; } ;
struct tee_context {struct tee_device* teedev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct tee_shm* ERR_PTR (int /*<<< orphan*/ ) ; 
 int TEE_SHM_DMA_BUF ; 
 int /*<<< orphan*/  get_dma_buf (int /*<<< orphan*/ ) ; 
 struct tee_shm* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct tee_shm *tee_shm_get_from_id(struct tee_context *ctx, int id)
{
	struct tee_device *teedev;
	struct tee_shm *shm;

	if (!ctx)
		return ERR_PTR(-EINVAL);

	teedev = ctx->teedev;
	mutex_lock(&teedev->mutex);
	shm = idr_find(&teedev->idr, id);
	if (!shm || shm->ctx != ctx)
		shm = ERR_PTR(-EINVAL);
	else if (shm->flags & TEE_SHM_DMA_BUF)
		get_dma_buf(shm->dmabuf);
	mutex_unlock(&teedev->mutex);
	return shm;
}