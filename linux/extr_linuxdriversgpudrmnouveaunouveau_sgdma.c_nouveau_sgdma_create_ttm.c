#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_tt {int /*<<< orphan*/ * func; } ;
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;
struct TYPE_8__ {struct ttm_tt ttm; } ;
struct nouveau_sgdma_be {TYPE_4__ ttm; } ;
struct TYPE_6__ {scalar_t__ family; } ;
struct TYPE_5__ {TYPE_2__ info; } ;
struct TYPE_7__ {TYPE_1__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 struct nouveau_sgdma_be* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv04_sgdma_backend ; 
 int /*<<< orphan*/  nv50_sgdma_backend ; 
 scalar_t__ ttm_dma_tt_init (TYPE_4__*,struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 

struct ttm_tt *
nouveau_sgdma_create_ttm(struct ttm_buffer_object *bo, uint32_t page_flags)
{
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct nouveau_sgdma_be *nvbe;

	nvbe = kzalloc(sizeof(*nvbe), GFP_KERNEL);
	if (!nvbe)
		return NULL;

	if (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA)
		nvbe->ttm.ttm.func = &nv04_sgdma_backend;
	else
		nvbe->ttm.ttm.func = &nv50_sgdma_backend;

	if (ttm_dma_tt_init(&nvbe->ttm, bo, page_flags))
		/*
		 * A failing ttm_dma_tt_init() will call ttm_tt_destroy()
		 * and thus our nouveau_sgdma_destroy() hook, so we don't need
		 * to free nvbe here.
		 */
		return NULL;
	return &nvbe->ttm.ttm;
}