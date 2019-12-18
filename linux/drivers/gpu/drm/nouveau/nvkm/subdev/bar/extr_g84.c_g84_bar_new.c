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
 int /*<<< orphan*/  g84_bar_func ; 
 int nv50_bar_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,int,struct nvkm_bar**) ; 

int
g84_bar_new(struct nvkm_device *device, int index, struct nvkm_bar **pbar)
{
	return nv50_bar_new_(&g84_bar_func, device, index, 0x200, pbar);
}