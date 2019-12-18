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
struct nvkm_device {int dummy; } ;
struct nvkm_bar {int iomap_uncached; } ;

/* Variables and functions */
 int gf100_bar_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_bar**) ; 
 int /*<<< orphan*/  gm20b_bar_func ; 

int
gm20b_bar_new(struct nvkm_device *device, int index, struct nvkm_bar **pbar)
{
	int ret = gf100_bar_new_(&gm20b_bar_func, device, index, pbar);
	if (ret == 0)
		(*pbar)->iomap_uncached = true;
	return ret;
}