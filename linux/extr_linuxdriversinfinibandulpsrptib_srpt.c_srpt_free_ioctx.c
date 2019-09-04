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
struct srpt_ioctx {struct srpt_ioctx* buf; int /*<<< orphan*/  dma; } ;
struct srpt_device {int /*<<< orphan*/  device; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (struct srpt_ioctx*) ; 

__attribute__((used)) static void srpt_free_ioctx(struct srpt_device *sdev, struct srpt_ioctx *ioctx,
			    int dma_size, enum dma_data_direction dir)
{
	if (!ioctx)
		return;

	ib_dma_unmap_single(sdev->device, ioctx->dma, dma_size, dir);
	kfree(ioctx->buf);
	kfree(ioctx);
}