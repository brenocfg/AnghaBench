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
struct nvkm_therm {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv40_therm ; 
 int nvkm_therm_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_therm**) ; 

int
nv40_therm_new(struct nvkm_device *device, int index,
	       struct nvkm_therm **ptherm)
{
	return nvkm_therm_new_(&nv40_therm, device, index, ptherm);
}