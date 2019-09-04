#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ttm_tt {TYPE_1__* sg; int /*<<< orphan*/  bdev; } ;
struct amdgpu_ttm_tt {int userflags; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int AMDGPU_GEM_USERPTR_READONLY ; 
 int DMA_BIDIRECTIONAL ; 
 int DMA_TO_DEVICE ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ttm_tt_mark_user_pages (struct ttm_tt*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_1__*) ; 

__attribute__((used)) static void amdgpu_ttm_tt_unpin_userptr(struct ttm_tt *ttm)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(ttm->bdev);
	struct amdgpu_ttm_tt *gtt = (void *)ttm;

	int write = !(gtt->userflags & AMDGPU_GEM_USERPTR_READONLY);
	enum dma_data_direction direction = write ?
		DMA_BIDIRECTIONAL : DMA_TO_DEVICE;

	/* double check that we don't free the table twice */
	if (!ttm->sg->sgl)
		return;

	/* unmap the pages mapped to the device */
	dma_unmap_sg(adev->dev, ttm->sg->sgl, ttm->sg->nents, direction);

	/* mark the pages as dirty */
	amdgpu_ttm_tt_mark_user_pages(ttm);

	sg_free_table(ttm->sg);
}