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
struct nvkm_bar {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_bar_func ; 
 int gf100_bar_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_bar**) ; 

int
gf100_bar_new(struct nvkm_device *device, int index, struct nvkm_bar **pbar)
{
	return gf100_bar_new_(&gf100_bar_func, device, index, pbar);
}