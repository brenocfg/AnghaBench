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
struct nvkm_mc {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int gp100_mc_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_mc**) ; 
 int /*<<< orphan*/  gp10b_mc ; 

int
gp10b_mc_new(struct nvkm_device *device, int index, struct nvkm_mc **pmc)
{
	return gp100_mc_new_(&gp10b_mc, device, index, pmc);
}