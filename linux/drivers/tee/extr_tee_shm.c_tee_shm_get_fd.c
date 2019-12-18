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
struct tee_shm {int flags; int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int TEE_SHM_DMA_BUF ; 
 int dma_buf_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_buf (int /*<<< orphan*/ ) ; 

int tee_shm_get_fd(struct tee_shm *shm)
{
	int fd;

	if (!(shm->flags & TEE_SHM_DMA_BUF))
		return -EINVAL;

	get_dma_buf(shm->dmabuf);
	fd = dma_buf_fd(shm->dmabuf, O_CLOEXEC);
	if (fd < 0)
		dma_buf_put(shm->dmabuf);
	return fd;
}