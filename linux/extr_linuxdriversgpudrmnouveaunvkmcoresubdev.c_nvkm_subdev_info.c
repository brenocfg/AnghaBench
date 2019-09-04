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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_subdev {TYPE_1__* func; } ;
struct TYPE_2__ {int (* info ) (struct nvkm_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct nvkm_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
nvkm_subdev_info(struct nvkm_subdev *subdev, u64 mthd, u64 *data)
{
	if (subdev->func->info)
		return subdev->func->info(subdev, mthd, data);
	return -ENOSYS;
}