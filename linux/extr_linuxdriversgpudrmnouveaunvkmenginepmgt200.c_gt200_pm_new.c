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
struct nvkm_pm {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gt200_pm ; 
 int nv40_pm_new_ (int /*<<< orphan*/ ,struct nvkm_device*,int,struct nvkm_pm**) ; 

int
gt200_pm_new(struct nvkm_device *device, int index, struct nvkm_pm **ppm)
{
	return nv40_pm_new_(gt200_pm, device, index, ppm);
}