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
struct nvkm_devinit {int dummy; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int nv04_devinit_new_ (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_devinit**) ; 
 int /*<<< orphan*/  nv05_devinit ; 

int
nv05_devinit_new(struct nvkm_device *device, int index,
		 struct nvkm_devinit **pinit)
{
	return nv04_devinit_new_(&nv05_devinit, device, index, pinit);
}