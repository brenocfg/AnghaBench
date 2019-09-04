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
struct nvkm_fuse {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_fuse ; 
 int nvkm_fuse_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_fuse**) ; 

int
gf100_fuse_new(struct nvkm_device *device, int index, struct nvkm_fuse **pfuse)
{
	return nvkm_fuse_new_(&gf100_fuse, device, index, pfuse);
}