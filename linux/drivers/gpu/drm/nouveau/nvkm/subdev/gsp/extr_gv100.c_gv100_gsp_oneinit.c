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
struct nvkm_subdev {int /*<<< orphan*/  index; int /*<<< orphan*/  device; } ;
struct nvkm_gsp {int /*<<< orphan*/  falcon; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int nvkm_falcon_v1_new (struct nvkm_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvkm_gsp* nvkm_gsp (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_top_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gv100_gsp_oneinit(struct nvkm_subdev *subdev)
{
	struct nvkm_gsp *gsp = nvkm_gsp(subdev);

	gsp->addr = nvkm_top_addr(subdev->device, subdev->index);
	if (!gsp->addr)
		return -EINVAL;

	return nvkm_falcon_v1_new(subdev, "GSP", gsp->addr, &gsp->falcon);
}