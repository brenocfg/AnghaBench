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
struct TYPE_5__ {int oclass; } ;
struct TYPE_8__ {int /*<<< orphan*/  chan; TYPE_1__ copy; } ;
struct nouveau_drm {TYPE_4__ ttm; TYPE_3__* dmem; } ;
struct TYPE_6__ {int /*<<< orphan*/  chan; int /*<<< orphan*/  copy_func; } ;
struct TYPE_7__ {TYPE_2__ migrate; } ;

/* Variables and functions */
 int ENODEV ; 
#define  PASCAL_DMA_COPY_A 131 
#define  PASCAL_DMA_COPY_B 130 
#define  TURING_DMA_COPY_A 129 
#define  VOLTA_DMA_COPY_A 128 
 int /*<<< orphan*/  nvc0b5_migrate_copy ; 

__attribute__((used)) static int
nouveau_dmem_migrate_init(struct nouveau_drm *drm)
{
	switch (drm->ttm.copy.oclass) {
	case PASCAL_DMA_COPY_A:
	case PASCAL_DMA_COPY_B:
	case  VOLTA_DMA_COPY_A:
	case TURING_DMA_COPY_A:
		drm->dmem->migrate.copy_func = nvc0b5_migrate_copy;
		drm->dmem->migrate.chan = drm->ttm.chan;
		return 0;
	default:
		break;
	}
	return -ENODEV;
}