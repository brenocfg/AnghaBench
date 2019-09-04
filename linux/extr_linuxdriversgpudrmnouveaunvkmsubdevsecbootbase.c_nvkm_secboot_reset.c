#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvkm_secboot {TYPE_2__* acr; int /*<<< orphan*/  subdev; } ;
struct TYPE_4__ {unsigned long managed_falcons; TYPE_1__* func; } ;
struct TYPE_3__ {int (* reset ) (TYPE_2__*,struct nvkm_secboot*,unsigned long) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nvkm_error (int /*<<< orphan*/ *,char*) ; 
 int stub1 (TYPE_2__*,struct nvkm_secboot*,unsigned long) ; 

int
nvkm_secboot_reset(struct nvkm_secboot *sb, unsigned long falcon_mask)
{
	/* Unmanaged falcon? */
	if ((falcon_mask | sb->acr->managed_falcons) != sb->acr->managed_falcons) {
		nvkm_error(&sb->subdev, "cannot reset unmanaged falcon!\n");
		return -EINVAL;
	}

	return sb->acr->func->reset(sb->acr, sb, falcon_mask);
}